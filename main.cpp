
/////////////////////////////////////////////////////////////////////////////
//
// main.cpp - main source
//
/////////////////////////////////////////////////////////////////////////////

#include "cpr.h"

static const char * STATIC_pUsage =
  "usage: comp\n" \
  "  -huff <file> - compress file using static Huffman\n" \
  "  -lz1 <file> - compress file using static LZ77 variation 1 (window size=2048, hash table)\n" \
  "  -lz2 <file> - compress file using static LZ77 variation 2 (window size=4096, hash table)\n" \
  "  -lz3 <file> - compress file using static LZ77 variation 3 (window size=2048, linear)\n" \
  "  -lz4 <file> - compress file using static LZ77 variation 4 (window size=4096, linear)\n" \
  "  -expand <file> - expand file\n" \
  "  -h, --help - display help\n";

/////////////////////////////////////////////////////////////////////////////
__T_INT main(__T_INT iArgc, __T_CHAR * * pArgv) {
  __T_INT iResult = 0;

  try {
    // create running environment
    ::CPR::Create();

    // initialize running environment
    ::CPR::Initialize();

    // parse command line
    if (iArgc != 1) {
      REFERENCE< ::CPR::COMPRESSOR::CCompressor> tCompressor;
      REFERENCE< ::CPR::CInput> tInput;
      REFERENCE< ::CPR::COutput> tOutput;
      REFERENCE< ::CPR::COutput> tLog;
      T_CHAR tBenchmark[1024];
      __T_DOUBLE dUserTime = 0;
      __T_DOUBLE dElapsedTime = 0;

      if ((T_STRING(pArgv[1]) == "-huff") || (T_STRING(pArgv[1]) == "-lz1") || (T_STRING(pArgv[1]) == "-lz2") || (T_STRING(pArgv[1]) == "-lz3") || (T_STRING(pArgv[1]) == "-lz4") || (T_STRING(pArgv[1]) == "-expand")) {
        // create a new input
        if (iArgc > 2) {
          tInput.Create(new ::CPR::CInput(pArgv[2]));
        } else {
          tInput.Create(new ::CPR::CInput());
        }

        // create a new output
        tOutput.Create(new ::CPR::COutput());
        
        // start timer
        dUserTime = user_time();
        start_timer();

        if (T_STRING(pArgv[1]) == "-expand") {
          switch (tInput->ReadType()) {
          case ::CPR::HUFFMAN : {
            // create a new huffman compressor
            tCompressor.Create(new ::CPR::COMPRESSOR::CHuffman());     
            break;
          }
          case ::CPR::LZ77_1 : {
            // create a new lz77 compressor
            tCompressor.Create(new ::CPR::COMPRESSOR::CLZ77Hash(::CPR::LZ77_1));     
            break;
          }
          case ::CPR::LZ77_2 : {
            // create a new lz77 compressor
            tCompressor.Create(new ::CPR::COMPRESSOR::CLZ77Hash(::CPR::LZ77_2));     
            break;
          }
          case ::CPR::LZ77_3 : {
            // create a new lz77 compressor
            tCompressor.Create(new ::CPR::COMPRESSOR::CLZ77Linear(::CPR::LZ77_3));     
            break;
          }
          case ::CPR::LZ77_4 : {
            // create a new lz77 compressor
            tCompressor.Create(new ::CPR::COMPRESSOR::CLZ77Linear(::CPR::LZ77_4));     
            break;
          }
          }

          // expand input
          tCompressor->Expand(tInput->Read(), tOutput);
        } else {
          if (T_STRING(pArgv[1]) == "-huff") {
            // create a new huffman compressor
            tCompressor.Create(new ::CPR::COMPRESSOR::CHuffman());     
          } else if (T_STRING(pArgv[1]) == "-lz1") {
            // create a new lz77 compressor
            tCompressor.Create(new ::CPR::COMPRESSOR::CLZ77Hash(::CPR::LZ77_1, 2048));     
          } else if (T_STRING(pArgv[1]) == "-lz2") {
            // create a new lz77 compressor
            tCompressor.Create(new ::CPR::COMPRESSOR::CLZ77Hash(::CPR::LZ77_2, 4096));     
          } else if (T_STRING(pArgv[1]) == "-lz3") {
            // create a new lz77 compressor
            tCompressor.Create(new ::CPR::COMPRESSOR::CLZ77Hash(::CPR::LZ77_3, 2048));     
          } else if (T_STRING(pArgv[1]) == "-lz4") {
            // create a new lz77 compressor
            tCompressor.Create(new ::CPR::COMPRESSOR::CLZ77Hash(::CPR::LZ77_4, 4096));     
          }

          // write compressor type
          tOutput->WriteType(tCompressor->GetType());

          // compress input
          tCompressor->Compress(tInput->Read(), tOutput);
        }
        
        // get elapsed time
        dElapsedTime = elapsed_time();
          
        // create benchmark
        tLog.Create(new ::CPR::COutput("benchmark.log", ::CPR::CFile::APPEND));
        sprintf(tBenchmark, "%s | %d -> %d byte(s) | %4.2lf%% | cpu time: %lf\n", C_STR(tInput->GetName()), tInput->GetTotalRead(), tOutput->GetTotalWrite(), ((__T_DOUBLE)(tOutput->GetTotalWrite()) / (__T_DOUBLE)(tInput->GetTotalRead())) * (__T_DOUBLE)100.0, dElapsedTime);
        tLog->Write((T_BYTE *)tBenchmark, strlen(tBenchmark));
      } else if ((T_STRING(pArgv[1]) == "-h") || (T_STRING(pArgv[1]) == "--help")) {
        printf(::STATIC_pUsage);
      }
    } else {
      printf(::STATIC_pUsage);
    }

    // shutdown running environment
    ::CPR::Shutdown(true);

    // destroy running environment
    ::CPR::Destroy();
  } catch (::BASE::EException & tException) {
    printf("EXCEPTION: %d, %s\n", tException.GetCode(), C_STR(tException.GetMessage()));
  } catch (...) {
    printf("FATAL ERROR\n");
  }

  return (iResult);
} // main
