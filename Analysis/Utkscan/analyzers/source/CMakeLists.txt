set(ANALYZER_SOURCES
        CfdAnalyzer.cpp
        TauAnalyzer.cpp
        TraceExtractor.cpp
        TraceFilter.cpp
        TraceFilterAnalyzer.cpp
        TraceAnalyzer.cpp
        WaaAnalyzer.cpp
        WaveformAnalyzer.cpp)

if(USE_GSL)
    set(ANALYZER_SOURCES ${ANALYZER_SOURCES} FittingAnalyzer.cpp)
endif(USE_GSL)

add_library(AnalyzerObjects OBJECT ${ANALYZER_SOURCES})



