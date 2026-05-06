project('fuckcraft', ['c', 'cpp'])

glfw_dep = dependency('glfw3', required: true)

glad_inc = include_directories('glad/include')
glad_lib = static_library(
    'glad',
    'glad/src/glad.c',
    include_directories: glad_inc,
)

glm_dep = dependency('glm', required: true)

spng_dep = dependency('spng', required: true)

srcs = [
    'src/main.cpp',
    'src/window.cpp',
    'src/input.cpp',
    'src/render/mesh.cpp',
    'src/render/opengl.cpp',
    'src/render/shader.cpp',
    'src/render/texture.cpp',
    'src/player/camera.cpp',
    'src/player/player.cpp',
    'src/minecraft.cpp',
    'src/object/entitytransform.cpp',
    'src/object/blocktransform.cpp',
    'src/world/block.cpp',
    'src/world/world.cpp',
    'src/world/blockregistry.cpp',
    'src/loader/png.cpp'
]

executable(
    'fuckcraft',
    srcs,
    dependencies: [glfw_dep, glm_dep, spng_dep],
    link_with: [glad_lib],
    include_directories: [glad_inc, include_directories('src')]
)