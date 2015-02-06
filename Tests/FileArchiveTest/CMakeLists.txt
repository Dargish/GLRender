include_directories("${GLRENDER_SRC_DIR}")

add_glr_test(
	FileArchiveTest
		GlRender
		boost_serialization
	)
