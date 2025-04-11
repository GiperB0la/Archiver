#include "../include/Archiver.hpp"


void archive(const std::string& inputFile, const std::string& archiveFile, std::atomic<bool>& stopFlag)
{
    std::ifstream in(inputFile, std::ios::binary);
    std::ofstream out(archiveFile, std::ios::binary);
    if (!in || !out) throw std::runtime_error("[-] Failed to open input or output file");

    const size_t bufSize = ZSTD_CStreamOutSize();
    char* inBuf = new char[bufSize];
    char* outBuf = new char[bufSize];

    ZSTD_CStream* cstream = ZSTD_createCStream();
    ZSTD_initCStream(cstream, 1);

    while (!stopFlag && in) {
        in.read(inBuf, bufSize);
        ZSTD_inBuffer input = { inBuf, static_cast<size_t>(in.gcount()), 0 };

        while (input.pos < input.size) {
            ZSTD_outBuffer output = { outBuf, bufSize, 0 };
            ZSTD_compressStream(cstream, &output, &input);
            out.write(outBuf, output.pos);
        }
    }

    ZSTD_outBuffer output = { outBuf, bufSize, 0 };
    size_t remaining;
    do {
        remaining = ZSTD_endStream(cstream, &output);
        out.write(outBuf, output.pos);
    } while (remaining != 0);

    ZSTD_freeCStream(cstream);
    delete[] inBuf;
    delete[] outBuf;
}

void unzip(const std::string& archiveFile, const std::string& outputFile, std::atomic<bool>& stopFlag)
{
    std::ifstream in(archiveFile, std::ios::binary);
    std::ofstream out(outputFile, std::ios::binary);
    if (!in || !out) throw std::runtime_error("[-] Failed to open input or output file");

    const size_t bufSize = ZSTD_DStreamOutSize();
    char* inBuf = new char[bufSize];
    char* outBuf = new char[bufSize];

    ZSTD_DStream* dstream = ZSTD_createDStream();
    ZSTD_initDStream(dstream);

    while (!stopFlag && in) {
        in.read(inBuf, bufSize);
        ZSTD_inBuffer input = { inBuf, static_cast<size_t>(in.gcount()), 0 };

        while (input.pos < input.size) {
            ZSTD_outBuffer output = { outBuf, bufSize, 0 };
            ZSTD_decompressStream(dstream, &output, &input);
            out.write(outBuf, output.pos);
        }
    }

    ZSTD_freeDStream(dstream);
    delete[] inBuf;
    delete[] outBuf;
}