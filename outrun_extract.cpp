#include <ios>
#include <iostream>
#include <fstream>
using namespace std;

/* 
    The offset, size CRC32 of tracks taken from https://github.com/djyt/cannonball/wiki/Extracting-OutRun-Music-From-the-Switch-&-3DS
        0x77f807 Cruising Line: 24,369 bytes [CRC32: 70C83B74]
        0x786807 Camino A Mi Amor (Version 1): 22,488 bytes [CRC32: 0056B27D]
        0x78d807 Step On Beat (Arcade Version): 14,480 bytes [CRC32: 93BBCDAC]
        0x794807 Radiation: 28,274 bytes [CRC32: 1BAB7DDA]
        0x794807 Camino A Mi Amor (Version 2): 22,488 bytes [CRC32: C07D2D50]
        0x7a2807 Step On Beat (Megadrive Version): 10,503 bytes [CRC32: 7DB6F98E]
*/

// Struct that contains the information for a given track
struct TrackInfo
{
    string fileName; // The file name of the track
    streamsize size; // Size of the track in bytes
    streampos  offset; // Offset of the track
};

// extractAudio function prototype
void extractAudio(TrackInfo);

int main()
{
    // Constants for all the tracks to extract
    const TrackInfo CRUISING_LINE = {"switch_cruisingline.bin", 24369, 7862279};

    extractAudio(CRUISING_LINE);

    return 0;
}

// Extracts the audio track based on the given track
void extractAudio(TrackInfo track)
{
    // Open decompressed OutRun switch executable
    ifstream outRunFile("main_decompressed", ios::in | ios::binary);

    // Throw exception if decompressed OutRun switch  executable is not found
    if (outRunFile.fail())
    {
        throw "Decompressed OutRun Switch executable not found\n";
    }

    char *buffer = new char[track.size]; // Buffer to hold track

    // Move read position to offeset and read bytes 
    outRunFile.seekg(track.offset);
    outRunFile.read(buffer, track.size);
    outRunFile.close();
    
    // Create Track Name.bin to write to
    ofstream outputFile(track.fileName, ios::out | ios::binary);
    
    // Throw exception if outputFile failed to create track file
    if (outputFile.fail())
    {
        throw "Failed to create track bin file\n";
    }

    // Write buffer to outputFile and close it
    outputFile.write(buffer, track.size);
    outputFile.close();

    delete [] buffer;
}
