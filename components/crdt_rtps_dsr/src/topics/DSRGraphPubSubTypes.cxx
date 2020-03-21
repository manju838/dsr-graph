// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file DSRGraphPubSubTypes.cpp
 * This header file contains the implementation of the serialization functions.
 *
 * This file was generated by the tool fastcdrgen.
 */


#include <fastcdr/FastBuffer.h>
#include <fastcdr/Cdr.h>

#include "DSRGraphPubSubTypes.h"

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;

EdgeAttribsPubSubType::EdgeAttribsPubSubType()
{
    setName("EdgeAttribs");
    m_typeSize = static_cast<uint32_t>(EdgeAttribs::getMaxCdrSerializedSize()) + 4 /*encapsulation*/;
    m_isGetKeyDefined = EdgeAttribs::isKeyDefined();
    size_t keyLength = EdgeAttribs::getKeyMaxCdrSerializedSize()>16 ? EdgeAttribs::getKeyMaxCdrSerializedSize() : 16;
    m_keyBuffer = reinterpret_cast<unsigned char*>(malloc(keyLength));
    memset(m_keyBuffer, 0, keyLength);
}

EdgeAttribsPubSubType::~EdgeAttribsPubSubType()
{
    if(m_keyBuffer!=nullptr)
        free(m_keyBuffer);
}

bool EdgeAttribsPubSubType::serialize(void *data, SerializedPayload_t *payload)
{
    EdgeAttribs *p_type = static_cast<EdgeAttribs*>(data);
    eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->max_size); // Object that manages the raw buffer.
    eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN,
            eprosima::fastcdr::Cdr::DDS_CDR); // Object that serializes the data.
    payload->encapsulation = ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;
    // Serialize encapsulation
    ser.serialize_encapsulation();

    try
    {
        p_type->serialize(ser); // Serialize the object:
    }
    catch(eprosima::fastcdr::exception::NotEnoughMemoryException& /*exception*/)
    {
        return false;
    }

    payload->length = static_cast<uint32_t>(ser.getSerializedDataLength()); //Get the serialized length
    return true;
}

bool EdgeAttribsPubSubType::deserialize(SerializedPayload_t* payload, void* data)
{
    EdgeAttribs* p_type = static_cast<EdgeAttribs*>(data); //Convert DATA to pointer of your type
    eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->length); // Object that manages the raw buffer.
    eprosima::fastcdr::Cdr deser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN,
            eprosima::fastcdr::Cdr::DDS_CDR); // Object that deserializes the data.
    // Deserialize encapsulation.
    deser.read_encapsulation();
    payload->encapsulation = deser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

    try
    {
        p_type->deserialize(deser); //Deserialize the object:
    }
    catch(eprosima::fastcdr::exception::NotEnoughMemoryException& /*exception*/)
    {
        return false;
    }

    return true;
}

std::function<uint32_t()> EdgeAttribsPubSubType::getSerializedSizeProvider(void* data)
{
    return [data]() -> uint32_t
    {
        return static_cast<uint32_t>(type::getCdrSerializedSize(*static_cast<EdgeAttribs*>(data))) + 4 /*encapsulation*/;
    };
}

void* EdgeAttribsPubSubType::createData()
{
    return reinterpret_cast<void*>(new EdgeAttribs());
}

void EdgeAttribsPubSubType::deleteData(void* data)
{
    delete(reinterpret_cast<EdgeAttribs*>(data));
}

bool EdgeAttribsPubSubType::getKey(void *data, InstanceHandle_t* handle, bool force_md5)
{
    if(!m_isGetKeyDefined)
        return false;
    EdgeAttribs* p_type = static_cast<EdgeAttribs*>(data);
    eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(m_keyBuffer),EdgeAttribs::getKeyMaxCdrSerializedSize());     // Object that manages the raw buffer.
    eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::BIG_ENDIANNESS);     // Object that serializes the data.
    p_type->serializeKey(ser);
    if(force_md5 || EdgeAttribs::getKeyMaxCdrSerializedSize()>16)    {
        m_md5.init();
        m_md5.update(m_keyBuffer, static_cast<unsigned int>(ser.getSerializedDataLength()));
        m_md5.finalize();
        for(uint8_t i = 0;i<16;++i)        {
            handle->value[i] = m_md5.digest[i];
        }
    }
    else    {
        for(uint8_t i = 0;i<16;++i)        {
            handle->value[i] = m_keyBuffer[i];
        }
    }
    return true;
}

ContentPubSubType::ContentPubSubType()
{
    setName("Content");
    m_typeSize = static_cast<uint32_t>(Content::getMaxCdrSerializedSize()) + 4 /*encapsulation*/;
    m_isGetKeyDefined = Content::isKeyDefined();
    size_t keyLength = Content::getKeyMaxCdrSerializedSize()>16 ? Content::getKeyMaxCdrSerializedSize() : 16;
    m_keyBuffer = reinterpret_cast<unsigned char*>(malloc(keyLength));
    memset(m_keyBuffer, 0, keyLength);
}

ContentPubSubType::~ContentPubSubType()
{
    if(m_keyBuffer!=nullptr)
        free(m_keyBuffer);
}

bool ContentPubSubType::serialize(void *data, SerializedPayload_t *payload)
{
    Content *p_type = static_cast<Content*>(data);
    eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->max_size); // Object that manages the raw buffer.
    eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN,
            eprosima::fastcdr::Cdr::DDS_CDR); // Object that serializes the data.
    payload->encapsulation = ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;
    // Serialize encapsulation
    ser.serialize_encapsulation();

    try
    {
        p_type->serialize(ser); // Serialize the object:
    }
    catch(eprosima::fastcdr::exception::NotEnoughMemoryException& /*exception*/)
    {
        return false;
    }

    payload->length = static_cast<uint32_t>(ser.getSerializedDataLength()); //Get the serialized length
    return true;
}

bool ContentPubSubType::deserialize(SerializedPayload_t* payload, void* data)
{
    Content* p_type = static_cast<Content*>(data); //Convert DATA to pointer of your type
    eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->length); // Object that manages the raw buffer.
    eprosima::fastcdr::Cdr deser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN,
            eprosima::fastcdr::Cdr::DDS_CDR); // Object that deserializes the data.
    // Deserialize encapsulation.
    deser.read_encapsulation();
    payload->encapsulation = deser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

    try
    {
        p_type->deserialize(deser); //Deserialize the object:
    }
    catch(eprosima::fastcdr::exception::NotEnoughMemoryException& /*exception*/)
    {
        return false;
    }

    return true;
}

std::function<uint32_t()> ContentPubSubType::getSerializedSizeProvider(void* data)
{
    return [data]() -> uint32_t
    {
        return static_cast<uint32_t>(type::getCdrSerializedSize(*static_cast<Content*>(data))) + 4 /*encapsulation*/;
    };
}

void* ContentPubSubType::createData()
{
    return reinterpret_cast<void*>(new Content());
}

void ContentPubSubType::deleteData(void* data)
{
    delete(reinterpret_cast<Content*>(data));
}

bool ContentPubSubType::getKey(void *data, InstanceHandle_t* handle, bool force_md5)
{
    if(!m_isGetKeyDefined)
        return false;
    Content* p_type = static_cast<Content*>(data);
    eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(m_keyBuffer),Content::getKeyMaxCdrSerializedSize());     // Object that manages the raw buffer.
    eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::BIG_ENDIANNESS);     // Object that serializes the data.
    p_type->serializeKey(ser);
    if(force_md5 || Content::getKeyMaxCdrSerializedSize()>16)    {
        m_md5.init();
        m_md5.update(m_keyBuffer, static_cast<unsigned int>(ser.getSerializedDataLength()));
        m_md5.finalize();
        for(uint8_t i = 0;i<16;++i)        {
            handle->value[i] = m_md5.digest[i];
        }
    }
    else    {
        for(uint8_t i = 0;i<16;++i)        {
            handle->value[i] = m_keyBuffer[i];
        }
    }
    return true;
}

DSRGraphTopicPubSubType::DSRGraphTopicPubSubType()
{
    setName("DSRGraphTopic");
    m_typeSize = static_cast<uint32_t>(DSRGraphTopic::getMaxCdrSerializedSize()) + 4 /*encapsulation*/;
    m_isGetKeyDefined = DSRGraphTopic::isKeyDefined();
    size_t keyLength = DSRGraphTopic::getKeyMaxCdrSerializedSize()>16 ? DSRGraphTopic::getKeyMaxCdrSerializedSize() : 16;
    m_keyBuffer = reinterpret_cast<unsigned char*>(malloc(keyLength));
    memset(m_keyBuffer, 0, keyLength);
}

DSRGraphTopicPubSubType::~DSRGraphTopicPubSubType()
{
    if(m_keyBuffer!=nullptr)
        free(m_keyBuffer);
}

bool DSRGraphTopicPubSubType::serialize(void *data, SerializedPayload_t *payload)
{
    DSRGraphTopic *p_type = static_cast<DSRGraphTopic*>(data);
    eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->max_size); // Object that manages the raw buffer.
    eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN,
            eprosima::fastcdr::Cdr::DDS_CDR); // Object that serializes the data.
    payload->encapsulation = ser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;
    // Serialize encapsulation
    ser.serialize_encapsulation();

    try
    {
        p_type->serialize(ser); // Serialize the object:
    }
    catch(eprosima::fastcdr::exception::NotEnoughMemoryException& /*exception*/)
    {
        return false;
    }

    payload->length = static_cast<uint32_t>(ser.getSerializedDataLength()); //Get the serialized length
    return true;
}

bool DSRGraphTopicPubSubType::deserialize(SerializedPayload_t* payload, void* data)
{
    DSRGraphTopic* p_type = static_cast<DSRGraphTopic*>(data); //Convert DATA to pointer of your type
    eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(payload->data), payload->length); // Object that manages the raw buffer.
    eprosima::fastcdr::Cdr deser(fastbuffer, eprosima::fastcdr::Cdr::DEFAULT_ENDIAN,
            eprosima::fastcdr::Cdr::DDS_CDR); // Object that deserializes the data.
    // Deserialize encapsulation.
    deser.read_encapsulation();
    payload->encapsulation = deser.endianness() == eprosima::fastcdr::Cdr::BIG_ENDIANNESS ? CDR_BE : CDR_LE;

    try
    {
        p_type->deserialize(deser); //Deserialize the object:
    }
    catch(eprosima::fastcdr::exception::NotEnoughMemoryException& /*exception*/)
    {
        return false;
    }

    return true;
}

std::function<uint32_t()> DSRGraphTopicPubSubType::getSerializedSizeProvider(void* data)
{
    return [data]() -> uint32_t
    {
        return static_cast<uint32_t>(type::getCdrSerializedSize(*static_cast<DSRGraphTopic*>(data))) + 4 /*encapsulation*/;
    };
}

void* DSRGraphTopicPubSubType::createData()
{
    return reinterpret_cast<void*>(new DSRGraphTopic());
}

void DSRGraphTopicPubSubType::deleteData(void* data)
{
    delete(reinterpret_cast<DSRGraphTopic*>(data));
}

bool DSRGraphTopicPubSubType::getKey(void *data, InstanceHandle_t* handle, bool force_md5)
{
    if(!m_isGetKeyDefined)
        return false;
    DSRGraphTopic* p_type = static_cast<DSRGraphTopic*>(data);
    eprosima::fastcdr::FastBuffer fastbuffer(reinterpret_cast<char*>(m_keyBuffer),DSRGraphTopic::getKeyMaxCdrSerializedSize());     // Object that manages the raw buffer.
    eprosima::fastcdr::Cdr ser(fastbuffer, eprosima::fastcdr::Cdr::BIG_ENDIANNESS);     // Object that serializes the data.
    p_type->serializeKey(ser);
    if(force_md5 || DSRGraphTopic::getKeyMaxCdrSerializedSize()>16)    {
        m_md5.init();
        m_md5.update(m_keyBuffer, static_cast<unsigned int>(ser.getSerializedDataLength()));
        m_md5.finalize();
        for(uint8_t i = 0;i<16;++i)        {
            handle->value[i] = m_md5.digest[i];
        }
    }
    else    {
        for(uint8_t i = 0;i<16;++i)        {
            handle->value[i] = m_keyBuffer[i];
        }
    }
    return true;
}

