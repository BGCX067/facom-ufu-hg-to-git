##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=ed2
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "J:\facom-ufu\prj"
ProjectPath            := "J:\facom-ufu\prj"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Rea
Date                   :=04/13/10
CodeLitePath           :="d:\Arquivos de programas\CodeLite"
LinkerName             :=gcc
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=gcc
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=
MakeDirCommand         :=makedir
CmpOptions             := -ggdb $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)." 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
UNIT_TEST_PP_SRC_DIR:=J:\UnitTest++-1.3
WXCFG:=gcc_dll\mswu
WXWIN:=J:\wxWidgets-2.8.10
Objects=../ED1-T1/$(IntermediateDirectory)/main$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
../ED1-T1/$(IntermediateDirectory)/main$(ObjectSuffix): ../ED1-T1/main.c ../ED1-T1/$(IntermediateDirectory)/main$(DependSuffix)
	@$(MakeDirCommand) "../ED1-T1/Debug"
	$(C_CompilerName) $(SourceSwitch) "J:/facom-ufu/ED1-T1/main.c" $(CmpOptions) $(ObjectSwitch)../ED1-T1/$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
../ED1-T1/$(IntermediateDirectory)/main$(DependSuffix): ../ED1-T1/main.c
	@$(MakeDirCommand) "../ED1-T1/Debug"
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT../ED1-T1/$(IntermediateDirectory)/main$(ObjectSuffix) -MF../ED1-T1/$(IntermediateDirectory)/main$(DependSuffix) -MM "J:/facom-ufu/ED1-T1/main.c"


-include ../ED1-T1/$(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) ../ED1-T1/$(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) ../ED1-T1/$(IntermediateDirectory)/main$(DependSuffix)
	$(RM) ../ED1-T1/$(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile).exe


