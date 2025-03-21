#include "../include/errors.h"

#include "../include/sound_files/get_sound_file_info.h"

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>

void test_wav_file(void)
{

    SF_INFO info;

    int output = get_file_sound_info("../tests/test.wav", &info);

    CU_ASSERT_EQUAL(info.samplerate, 44100);
    CU_ASSERT_EQUAL(info.channels, 2);
    CU_ASSERT_EQUAL(info.format & SF_FORMAT_TYPEMASK, SF_FORMAT_WAV);
    CU_ASSERT_EQUAL(info.sections, 1);
    CU_ASSERT_EQUAL(info.seekable, 1);

    CU_ASSERT_EQUAL(output, 0);
}

void test_mp3_file(void)
{
    SF_INFO info;

    int output = get_file_sound_info("../tests/test.mp3", &info);

    CU_ASSERT_EQUAL(info.samplerate, 44100);
    CU_ASSERT_EQUAL(info.channels, 2);
    CU_ASSERT_EQUAL(info.format & SF_FORMAT_TYPEMASK, SF_FORMAT_MPEG);
    CU_ASSERT_EQUAL(info.sections, 1);
    CU_ASSERT_EQUAL(info.seekable, 1);

    CU_ASSERT_EQUAL(output, 0);
}

void test_ogg_file(void)
{
    SF_INFO info;

    int output = get_file_sound_info("../tests/test.ogg", &info);

    CU_ASSERT_EQUAL(info.samplerate, 44100);
    CU_ASSERT_EQUAL(info.channels, 2);
    CU_ASSERT_EQUAL(info.format & SF_FORMAT_TYPEMASK, SF_FORMAT_OGG);
    CU_ASSERT_EQUAL(info.sections, 1);
    CU_ASSERT_EQUAL(info.seekable, 1);

    CU_ASSERT_EQUAL(output, 0);
}

void test_not_found_file(void)
{
    SF_INFO info;

    int output = get_file_sound_info("overhere", &info);

    CU_ASSERT_NOT_EQUAL(output, 0);
}

void test_sd2_file(void)
{
    SF_INFO info;

    int output = get_file_sound_info("../tests/sample.sd4", &info);

    CU_ASSERT_NOT_EQUAL(output, 0);
}

void test_flac_file(void)
{
    SF_INFO info;

    int output = get_file_sound_info("../tests/sample.flac", &info);

    CU_ASSERT_EQUAL(info.samplerate, 96000);
    CU_ASSERT_EQUAL(info.channels, 2);
    CU_ASSERT_EQUAL(info.format & SF_FORMAT_TYPEMASK, SF_FORMAT_FLAC);
    CU_ASSERT_EQUAL(info.sections, 1);
    CU_ASSERT_EQUAL(info.seekable, 1);

    CU_ASSERT_EQUAL(output, 0);
}

void test_voc_file(void)
{
    SF_INFO info;

    int output = get_file_sound_info("../tests/sample.voc", &info);

    CU_ASSERT_EQUAL(info.samplerate, 44100);
    CU_ASSERT_EQUAL(info.channels, 2);
    CU_ASSERT_EQUAL(info.format & SF_FORMAT_TYPEMASK, SF_FORMAT_VOC);
    CU_ASSERT_EQUAL(info.sections, 1);
    CU_ASSERT_EQUAL(info.seekable, 1);

    CU_ASSERT_EQUAL(output, 0);
}

CU_TestInfo tests_get_sound_file_info[] = {
    {"Test wav sound file #1: File Info", test_wav_file},
    {"Test mp3 sound file #2: File Info", test_mp3_file},
    {"Test ogg sound file #3: File Info", test_ogg_file},
    {"Test sd2 sound file #4: File Info", test_sd2_file},
    {"Test flac sound file #5: File Info", test_flac_file},
    {"Test voc sound file #6: File Info", test_voc_file},
    {"Test sound file #7: File Not Found", test_not_found_file},

    CU_TEST_INFO_NULL};

CU_SuiteInfo suite_sound_files[] = {
    {"Suite tests for get_sound_file function", NULL, NULL, NULL, NULL, tests_get_sound_file_info},
    CU_SUITE_INFO_NULL};

int main(void)
{
    CU_ErrorCode init_test_registry = CU_initialize_registry();

    if (init_test_registry == CUE_SUCCESS)
    {

        CU_ErrorCode suite_status = CU_register_suites(suite_sound_files);

        if (suite_status == CUE_SUCCESS)
        {
            // Verbose output of the tests on the console
            CU_basic_set_mode(CU_BRM_VERBOSE);
            CU_basic_run_tests();

            // Output files
            CU_set_output_filename("../tests/log_suite_tests_sound_files");
            CU_list_tests_to_file(); // (Listing & Results xml)
            CU_automated_run_tests();
        }

        if (suite_status == CUE_NOMEMORY)
        {
            fprintf(stderr, "%s\n", MSG_FAIL_MEMORY_ALLOC);
            CU_cleanup_registry();
            return -1;
        }

        CU_cleanup_registry();
    }

    if (init_test_registry == CUE_NOMEMORY)
    {
        fprintf(stderr, "%s\n", MSG_FAIL_MEMORY_ALLOC);
        return -1;
    }

    return 0;
}