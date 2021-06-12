# Makefile
# all:より下の3行のインデント、
# gtest-gen:より下の1行のインデント
# は半角空白になっていますがタブ1個にしてください
# target.cはCなのでgccで、それ以外はC++なのでg++でビルドします
# gtest_main.ccはGoogleTestが用意してくれているmain関数、
# gtest-all.ccがGoogleTest全部入りファイルです
# -lpthreadをつけることにも注意。
# makeかmake allしたらビルドして実行まで行います。
all:
			gcc -c ../../modules/pl01_02_module.c
			g++ pl01_02_test.cpp ../../../vender/googletest/googletest/src/gtest_main.cc gtest/gtest-all.cc -I. -lpthread pl01_02_module.o
			./a.out
gtest-gen:
			python ../../../vender/googletest/googletest/scripts/fuse_gtest_files.py ./
clean:

			rm -f ./a.out
			rm -f ./pl01_02_module.o
