# Copyright (C) 2020 Gustavo Salomao
# All rights reserved.

#[rst
# openedk_add_module: Add module into the OpenEDK
# -----------------------------------------------
#
# .. code-block:: cmake
#
# openedk_add_module(NAME <name>
#                    DOMAIN <domain>
#                    SOURCES <sources>)
#
# Add a new module into the OpenEDK.
#
# The ``name`` must be the module's name.
# The ``domain`` is the domain/group of the module belongs to [OPTIONAL].
# The ``sources`` are the module's source files.
#
# Once the module is added, it creates targets following this name:
#   - openedk_<name>
#   - <domain>::<name>
#
# Example
# ^^^^^^^
#
# .. code-block:: cmake
#
# openedk_add_module(NAME foo
#                    DOMAIN bar
#                    SOURCES foo.c)
#
# The above code will create a module called 'foo' with the following targets:
#   - openedk_foo
#   - bar::foo
#
#]rst
macro(openedk_add_module)
  set(options "")
  set(oneValueArgs DOMAIN NAME)
  set(multiValueArgs SOURCES)

  cmake_parse_arguments(MODULE
                        "${options}"
                        "${oneValueArgs}"
                        "${multiValueArgs}"
                        ${ARGN})

  string(TOLOWER "${MODULE_NAME}" MODULE_NAME)
  string(TOLOWER "${MODULE_DOMAIN}" MODULE_DOMAIN)
  set(MODULE_TARGET "openedk_${MODULE_NAME}")

  add_library(${MODULE_TARGET} STATIC ${MODULE_SOURCES})
  target_include_directories(${MODULE_TARGET} PUBLIC
                             ${PROJECT_SOURCE_DIR}/include)

  if (NOT "${MODULE_DOMAIN}" STREQUAL "")
    add_library(${MODULE_DOMAIN}::${MODULE_NAME} ALIAS ${MODULE_TARGET})
  endif ()
endmacro()
