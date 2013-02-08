#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <string>

#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>

#include <libxml2/libxml/tree.h>

using namespace std;
using namespace google::protobuf;

inline void
ReadFieldValue(Message *message, const FieldDescriptor *field, xmlNode *node);

// public
inline void
ProtoReadXml(Message *message, xmlNode *node) {
	for (int index = 0; index < message->GetDescriptor()->field_count(); ++index) {
		const FieldDescriptor *field = message->GetDescriptor()->field(index);
		for (xmlNode *childNode = node->children; childNode != 0; childNode = childNode->next) {
			if (childNode->type == XML_ELEMENT_NODE) {
				string name(reinterpret_cast<const char *>(childNode->name));
				if (field->name() == name)
					ReadFieldValue(message, field, childNode);
			}
		}
	}
}

// private
inline void
ReadFieldValue(Message *message, const FieldDescriptor *field, xmlNode *node) {
	string value;
	for (xmlNode *childNode = node->children; childNode != 0; childNode = childNode->next) {
		if (childNode->content)
			value += reinterpret_cast<char *>(childNode->content);
	}
	switch (field->cpp_type()) {
	case FieldDescriptor::CPPTYPE_ENUM:
	{
		for (int index = 0; index < field->enum_type()->value_count(); ++index) {
			string name(field->enum_type()->value(index)->name());
			if (name == value)
				field->is_repeated() ?
						message->GetReflection()->AddEnum(message, field, field->enum_type()->value(index)) :
						message->GetReflection()->SetEnum(message, field, field->enum_type()->value(index));
		}
		break;
	}
	case FieldDescriptor::CPPTYPE_STRING:
		field->is_repeated() ?
				message->GetReflection()->AddString(message, field, value) :
				message->GetReflection()->SetString(message, field, value);
		break;
	case FieldDescriptor::CPPTYPE_MESSAGE:
		field->is_repeated() ?
				ProtoReadXml(message->GetReflection()->AddMessage(message, field, 0), node) :
				ProtoReadXml(message->GetReflection()->MutableMessage(message, field, 0), node);
		break;
	default:
		break;
	}
}
