include(FetchContent)

FetchContent_Declare(
    cutils
    GIT_REPOSITORY https://github.com/umarnurmatov/cutils.git
    GIT_TAG a143933976bbf82f758dc845bf6d3e74a7b6a5cf
    GIT_SHALLOW true
)
FetchContent_MakeAvailable(cutils)
