include(FetchContent)

FetchContent_Declare(
    cutils
    GIT_REPOSITORY https://github.com/umarnurmatov/cutils.git
    GIT_TAG f09ce92e3b2339701554fa7b7c7e954f24e66524
    GIT_SHALLOW true
)
FetchContent_MakeAvailable(cutils)
