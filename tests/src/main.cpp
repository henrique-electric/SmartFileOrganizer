#include <gtest/gtest.h>


extern "C"
{
	#include "../../include/image_files/get_image_files.h"
	#include "../../include/errors.h"
	#include "../../include/file_type_detector.h"
};

TEST(get_file_type, get_file_types)
{
    	file_info info;

    	int output = get_file_type("hello.txt", &info);
    	get_file_size("hello.txt", &info);
    	EXPECT_EQ(output, 0);
    	EXPECT_EQ(true, info.success_analyse);
	EXPECT_STREQ(info.type, "Unicode");
    	EXPECT_EQ(info.file_size, 28105);
}


int main(int argc, char **argv)
{

        testing::InitGoogleTest(&argc, argv); 
        return RUN_ALL_TESTS(); 
        
}

