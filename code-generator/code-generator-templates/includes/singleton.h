{# -*- mode: fundamental -*- -#}
{%- macro singleton(class_name) -%}
public:
  static {{class_name}} & instance()
  {
    static {{class_name}} m_instance;
    return m_instance;
  }

  // delete copy and move constructors and assign operators
  {{class_name}}(const {{class_name}} &) = delete;
  {{class_name}}({{class_name}} &&) = delete;
  {{class_name}} & operator=(const {{class_name}} &) = delete;
  {{class_name}} & operator=({{class_name}} &&) = delete;

protected:
  {{class_name}}();
  ~{{class_name}}();
{%- endmacro -%}