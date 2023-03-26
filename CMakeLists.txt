CMAKE_MINIMUM_REQUIRED(VERSION 3.26.0)
PROJECT(bintree)

SET(HDR include/BTree.h)

SET(BUILD_EXAMPLE
    ON
    CACHE
    BOOL "Flag to build the example."
)

SET(BUILD_TEST
    OFF
    CACHE
    BOOL "Flag to build the test."
)

IF(BUILD_EXAMPLE)
    SET(EX_SRC example/main.c)
    SET(EX_HDR example/example.h)
    ADD_EXECUTABLE(example ${HDR} ${EX_SRC} ${EX_HDR})
    TARGET_INCLUDE_DIRECTORIES(example PRIVATE "example" PUBLIC "include")
ENDIF()

IF (BUILD_TEST)
    ENABLE_TESTING()
    SET(TEST_SRC test/BTreeTest.c)
    SET(TEST_HDR
        ${HDR}
        test/BTreeTest.h
        test/ctest.h
    )
    ADD_EXECUTABLE(btTest ${TEST_SRC} ${TEST_HDR})
    TARGET_INCLUDE_DIRECTORIES(btTest PRIVATE "tests" PUBLIC "include")
    ADD_TEST(BinaryTreeTest btTest)
ENDIF()
