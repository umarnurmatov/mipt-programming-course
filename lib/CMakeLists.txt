include(FetchContent)

FetchContent_Declare(
    cutils
    GIT_REPOSITORY https://github.com/umarnurmatov/cutils.git
    GIT_TAG 31879afd278646a8a5a395194ac6efddfe8b2f9e
    GIT_SHALLOW true
)
FetchContent_MakeAvailable(cutils)
