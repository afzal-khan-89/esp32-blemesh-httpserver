set(srcs "main.c"
        "board.c"
        "httserv.c"
        "wifist.c")

idf_component_register(SRCS "httserv.c" "wifist.c" "${srcs}"
                    INCLUDE_DIRS  ".")
