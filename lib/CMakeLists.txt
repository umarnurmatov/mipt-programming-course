include(FetchContent)

FetchContent_Declare(
    cutils
    GIT_REPOSITORY https://github.com/umarnurmatov/cutils.git
    GIT_TAG f8a10fb870d66b5925c92ce342cd301fa6ee1044
    GIT_SHALLOW true
)
FetchContent_MakeAvailable(cutils)
