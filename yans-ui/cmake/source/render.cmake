cmake_minimum_required( VERSION 3.7 )

list( APPEND YANS_UI_SOURCES
    src/render/detail/GameRenderer.cpp
    src/render/detail/RenderThread.cpp
    src/render/detail/TextureNode.cpp
)

list( APPEND YANS_UI_HEADERS
    src/render/detail/GameRenderer.h
    src/render/detail/RenderThread.h
    src/render/detail/TextureNode.h
)
