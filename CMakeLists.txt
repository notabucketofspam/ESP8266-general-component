set(COMPONENT_SRCS 
  "general_component/general_control.c"
  "general_component/general_network.c"
  "general_component/general_server.c"
  "general_component/general_storage.c"
)
set(COMPONENT_ADD_INCLUDEDIRS include/general_component)

register_component()
