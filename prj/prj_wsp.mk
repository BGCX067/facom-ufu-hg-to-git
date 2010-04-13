.PHONY: clean All

All:
	@echo ----------Building project:[ ed2 - Debug ]----------
	@"mingw32-make.exe"  -j 1 -f "ed2.mk"
clean:
	@echo ----------Cleaning project:[ ed2 - Debug ]----------
	@"mingw32-make.exe"  -j 1 -f "ed2.mk" clean
