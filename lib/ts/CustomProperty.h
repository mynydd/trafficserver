#ifndef CUSTOM_PROPERTY_H
#define CUSTOM_PROPERTY_H

#include <map>
#include <string>

class CustomProperties
{
public:
  CustomProperties();
  ~CustomProperties();
  void add(const char *name, void *value, void(*destroyValue)(void*));
  void remove(const char *name);
  void* get(const char *name);
private:
  CustomProperties(const CustomProperties&);
  CustomProperties operator=(const CustomProperties&);

  struct PropertyValue
  {
      PropertyValue(void *value = nullptr, void(*destroyFunc)(void*) = nullptr);
      void *m_value;
      void (*m_destroyFunc)(void*);
      void destroy();
  };
  std::map<std::string, PropertyValue> m_properties;
};

#endif
