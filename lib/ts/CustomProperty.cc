#include "CustomProperty.h"

CustomProperties::PropertyValue::PropertyValue(void *value, void(*destroyFunc)(void*))
  : m_value(value), m_destroyFunc(destroyFunc)
{
}

void CustomProperties::PropertyValue::destroy()
{
  if ((m_destroyFunc != nullptr) && (m_value != nullptr))
  {
    m_destroyFunc(m_value);
    m_destroyFunc = nullptr;
    m_value = nullptr;
  }
}

CustomProperties::CustomProperties() 
{
}

CustomProperties::~CustomProperties()
{
  for ( auto entry : m_properties )
  {
    entry.second.destroy();
  }
}

void CustomProperties::add(const char *name, void *value, void(*destroyValue)(void*))
{
  remove(name);
  m_properties.insert(std::make_pair(name, PropertyValue(value, destroyValue)));
}

void CustomProperties::remove(const char *name)
{
  auto i = m_properties.find(name);
  if ( i != m_properties.end())
  {
    i->second.destroy();
    m_properties.erase(i);
  }
}

void* CustomProperties::get(const char *name)
{ 
  auto i = m_properties.find(name);
  return i == m_properties.end() ? nullptr : i->second.m_value;
}
