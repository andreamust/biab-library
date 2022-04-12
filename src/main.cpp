/* Copyright (c) 2005 Andrew Choi.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification [*], are permitted for non-commercial purposes provided
that the following conditions are met:

1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this
software must display the following acknowledgement:

  This product includes software developed by Andrew Choi.

4. The name "Andrew Choi" may not be used to endorse or promote
products derived from this software without specific prior written
permission.

THIS SOFTWARE IS PROVIDED BY ANDREW CHOI "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED.  IN NO EVENT SHALL ANDREW CHOI BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

[*] Modifications to source code include, but are not limited to,
translation to other programming languages and use of its tables and
constant definitions.  */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <pybind11/pybind11.h>

namespace py = pybind11;


// namespace fs = std::filesystem;

static const char *rootNames[] = {"C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B", "C#", "D#", "F#",
                                  "G#", "A#"};

static const char *typeNames[] = {
        "",  /* 1 */
        "Maj",  /* 2 */
        "b5",  /* 3 */
        "aug",  /* 4 */
        "6",  /* 5 */
        "Maj7",  /* 6 */
        "Maj9",  /* 7 */
        "Maj9#11",  /* 8 */
        "Maj13#11",  /* 9 */
        "Maj13",  /* 10 */
        "Maj9(no 3)",  /* 11 */
        "+",  /* 12 */
        "Maj7#5",  /* 13 */
        "69",  /* 14 */
        "2",  /* 15 */
        "m",  /* 16 */
        "maug",  /* 17 */
        "mMaj7",  /* 18 */
        "m7",  /* 19 */
        "m9",  /* 20 */
        "m11",  /* 21 */
        "m13",  /* 22 */
        "m6",  /* 23 */
        "m#5",  /* 24 */
        "m7#5",  /* 25 */
        "?",  /* 26 */
        "?",  /* 27 */
        "?",  /* 28 */
        "?",  /* 29 */
        "?",  /* 30 */
        "?",  /* 31 */
        "m7b5",  /* 32 */
        "dim",  /* 33 */
        "?",  /* 34 */
        "?",  /* 35 */
        "?",  /* 36 */
        "?",  /* 37 */
        "?",  /* 38 */
        "?",  /* 39 */
        "5",  /* 40 */
        "?",  /* 41 */
        "?",  /* 42 */
        "?",  /* 43 */
        "?",  /* 44 */
        "?",  /* 45 */
        "?",  /* 46 */
        "?",  /* 47 */
        "?",  /* 48 */
        "?",  /* 49 */
        "?",  /* 50 */
        "?",  /* 51 */
        "?",  /* 52 */
        "?",  /* 53 */
        "?",  /* 54 */
        "?",  /* 55 */
        "7+",  /* 56 */
        "9+",  /* 57 */
        "13+",  /* 58 */
        "?",  /* 59 */
        "?",  /* 60 */
        "?",  /* 61 */
        "?",  /* 62 */
        "?",  /* 63 */
        "7",  /* 64 */
        "13",  /* 65 */
        "7b13",  /* 66 */
        "7#11",  /* 67 */
        "13#11",  /* 68 */
        "7#11b13",  /* 69 */
        "9",  /* 70 */
        "?",  /* 71 */
        "9b13",  /* 72 */
        "9#11",  /* 73 */
        "13#11",  /* 74 */
        "9#11b13",  /* 75 */
        "7b9",  /* 76 */
        "13b9",  /* 77 */
        "7b9b13",  /* 78 */
        "7b9#11",  /* 79 */
        "13b9#11",  /* 80 */
        "7b9#11b13",  /* 81 */
        "7#9",  /* 82 */
        "13#9",  /* 83 */
        "7#9b13",  /* 84 */
        "9#11",  /* 85 */
        "13#9#11",  /* 86 */
        "7#9#11b13",  /* 87 */
        "7b5",  /* 88 */
        "13b5",  /* 89 */
        "7b5b13",  /* 90 */
        "9b5",  /* 91 */
        "9b5b13",  /* 92 */
        "7b5b9",  /* 93 */
        "13b5b9",  /* 94 */
        "7b5b9b13",  /* 95 */
        "7b5#9",  /* 96 */
        "13b5#9",  /* 97 */
        "7b5#9b13",  /* 98 */
        "7#5",  /* 99 */
        "13#5",  /* 100 */
        "7#5#11",  /* 101 */
        "13#5#11",  /* 102 */
        "9#5",  /* 103 */
        "9#5#11",  /* 104 */
        "7#5b9",  /* 105 */
        "13#5b9",  /* 106 */
        "7#5b9#11",  /* 107 */
        "13#5b9#11",  /* 108 */
        "7#5#9",  /* 109 */
        "13#5#9#11",  /* 110 */
        "7#5#9#11",  /* 111 */
        "13#5#9#11",  /* 112 */
        "7alt",  /* 113 */
        "?",  /* 114 */
        "?",  /* 115 */
        "?",  /* 116 */
        "?",  /* 117 */
        "?",  /* 118 */
        "?",  /* 119 */
        "?",  /* 120 */
        "?",  /* 121 */
        "?",  /* 122 */
        "?",  /* 123 */
        "?",  /* 124 */
        "?",  /* 125 */
        "?",  /* 126 */
        "?",  /* 127 */
        "7sus",  /* 128 */
        "13sus",  /* 129 */
        "7susb13",  /* 130 */
        "7sus#11",  /* 131 */
        "13sus#11",  /* 132 */
        "7sus#11b13",  /* 133 */
        "9sus",  /* 134 */
        "?",  /* 135 */
        "9susb13",  /* 136 */
        "9sus#11",  /* 137 */
        "13sus#11",  /* 138 */
        "9sus#11b13",  /* 139 */
        "7susb9",  /* 140 */
        "13susb9",  /* 141 */
        "7susb913",  /* 142 */
        "7susb9#11",  /* 143 */
        "13susb9#11",  /* 144 */
        "7susb9#11b13",  /* 145 */
        "7sus#9",  /* 146 */
        "13sus#9",  /* 147 */
        "7sus#9b13",  /* 148 */
        "9sus#11",  /* 149 */
        "13sus#9#11",  /* 150 */
        "7sus#9#11b13",  /* 151 */
        "7susb5",  /* 152 */
        "13susb5",  /* 153 */
        "7susb5b13",  /* 154 */
        "9susb5",  /* 155 */
        "9susb5b13",  /* 156 */
        "7susb5b9",  /* 157 */
        "13susb5b9",  /* 158 */
        "7susb5b9b13",  /* 159 */
        "7susb5#9",  /* 160 */
        "13susb5#9",  /* 161 */
        "7susb5#9b13",  /* 162 */
        "7sus#5",  /* 163 */
        "13sus#5",  /* 164 */
        "7sus#5#11",  /* 165 */
        "13sus#5#11",  /* 166 */
        "9sus#5",  /* 167 */
        "9sus#5#11",  /* 168 */
        "7sus#5b9",  /* 169 */
        "13sus#5b9",  /* 170 */
        "7sus#5b9#11",  /* 171 */
        "13sus#5b9#11",  /* 172 */
        "7sus#5#9",  /* 173 */
        "13sus#5#9#11",  /* 174 */
        "7sus#5#9#11",  /* 175 */
        "13sus#5#9#11",  /* 176 */
        "4",  /* 177 */
        "?",  /* 178 */
        "?",  /* 179 */
        "?",  /* 180 */
        "?",  /* 181 */
        "?",  /* 182 */
        "?",  /* 183 */
        "sus",  /* 184 */
        /* no chord names above 185 */
};


static const char *harteNames[] = {
        "",  /* 1 */
        ":maj",  /* 2 */
        ":(b5)",  /* 3 */
        ":aug",  /* 4 */
        ":(6)",  /* 5 */
        ":maj7",  /* 6 */
        ":maj9",  /* 7 */
        ":maj(9,#11)",  /* 8 */
        ":maj(13,#11)",  /* 9 */
        ":maj(13)",  /* 10 */
        ":maj(9,*3)",  /* 11 */
        ":maj",  /* 12 */
        ":maj(7,#5)",  /* 13 */
        ":(6,9)",  /* 14 */
        ":(2)",  /* 15 */
        ":min",  /* 16 */
        ":min(#5)",  /* 17 */
        ":min7",  /* 18 */
        ":min7",  /* 19 */
        ":min(9)",  /* 20 */
        ":min(11)",  /* 21 */
        ":min(13)",  /* 22 */
        ":min(6)",  /* 23 */
        ":min(#5)",  /* 24 */
        ":min7(#5)",  /* 25 */
        "?",  /* 26 */
        "?",  /* 27 */
        "?",  /* 28 */
        "?",  /* 29 */
        "?",  /* 30 */
        "?",  /* 31 */
        ":min7(b5)",  /* 32 */
        ":dim",  /* 33 */
        "?",  /* 34 */
        "?",  /* 35 */
        "?",  /* 36 */
        "?",  /* 37 */
        "?",  /* 38 */
        "?",  /* 39 */
        ":(5)",  /* 40 */
        "?",  /* 41 */
        "?",  /* 42 */
        "?",  /* 43 */
        "?",  /* 44 */
        "?",  /* 45 */
        "?",  /* 46 */
        "?",  /* 47 */
        "?",  /* 48 */
        "?",  /* 49 */
        "?",  /* 50 */
        "?",  /* 51 */
        "?",  /* 52 */
        "?",  /* 53 */
        "?",  /* 54 */
        "?",  /* 55 */
        ":(7)",  /* 56 */
        ":(9)",  /* 57 */
        ":(13)",  /* 58 */
        "?",  /* 59 */
        "?",  /* 60 */
        "?",  /* 61 */
        "?",  /* 62 */
        "?",  /* 63 */
        ":(7)",  /* 64 */
        ":(13)",  /* 65 */
        ":(7,b13)",  /* 66 */
        ":(7,#11)",  /* 67 */
        ":(13,#11)",  /* 68 */
        ":(7,#11,b13)",  /* 69 */
        ":(9)",  /* 70 */
        "?",  /* 71 */
        ":(9,b13)",  /* 72 */
        ":(9,#11)",  /* 73 */
        ":(13,#11)",  /* 74 */
        ":(9,#11,b13)",  /* 75 */
        ":(7,b9)",  /* 76 */
        ":(13,b9)",  /* 77 */
        ":(7,b9,b13)",  /* 78 */
        ":(7,b9,#11)",  /* 79 */
        ":(13,b9,#11)",  /* 80 */
        ":(7b9#11b13",  /* 81 */
        ":(7,#9)",  /* 82 */
        ":(13,#9)",  /* 83 */
        ":(7,#9,b13)",  /* 84 */
        ":(9,#11)",  /* 85 */
        ":(13,#9,#11)",  /* 86 */
        ":(7,#9,#11,b13)",  /* 87 */
        ":(7,b5)",  /* 88 */
        ":(13,b5)",  /* 89 */
        ":(7,b5,b13)",  /* 90 */
        ":(9,b5)",  /* 91 */
        ":(9,b5.,b13)",  /* 92 */
        ":(7,b5,b9)",  /* 93 */
        ":(13,b5,b9)",  /* 94 */
        ":(7,b5,b9,b13",  /* 95 */
        ":(7,b5,#9)",  /* 96 */
        ":(13,b5,#9)",  /* 97 */
        ":(7,b5,#9,b13)",  /* 98 */
        ":(7,#5)",  /* 99 */
        ":(13,#5)",  /* 100 */
        ":(7,#5,#11)",  /* 101 */
        ":(13,#5,#11)",  /* 102 */
        ":(9,#5)",  /* 103 */
        ":(9,#5,#11)",  /* 104 */
        ":(7,#5,b9)",  /* 105 */
        ":(13,#5,b9)",  /* 106 */
        ":(7,#5,b9,#11)",  /* 107 */
        ":(13,#5,b9,#11)",  /* 108 */
        ":(7,#5,#9)",  /* 109 */
        ":(13,#5,#9,#11)",  /* 110 */
        ":(7,#5,#9,#11)",  /* 111 */
        ":(13,#5,#9,#11)",  /* 112 */
        ":(b7)",  /* 113 */
        "?",  /* 114 */
        "?",  /* 115 */
        "?",  /* 116 */
        "?",  /* 117 */
        "?",  /* 118 */
        "?",  /* 119 */
        "?",  /* 120 */
        "?",  /* 121 */
        "?",  /* 122 */
        "?",  /* 123 */
        "?",  /* 124 */
        "?",  /* 125 */
        "?",  /* 126 */
        "?",  /* 127 */
        ":(7,*3)",  /* 128 */
        ":(13,*3)",  /* 129 */
        ":(7, +3,b13)",  /* 130 */
        ":(7,*3,#11)",  /* 131 */
        ":(13,*3,#11)",  /* 132 */
        ":(7,*3,#11,b13)",  /* 133 */
        ":(9,*3)",  /* 134 */
        "?",  /* 135 */
        ":(9,*3,b13)",  /* 136 */
        ":(9,*3,#11)",  /* 137 */
        ":(13,*3,#11)",  /* 138 */
        ":(9,*3,#11,b13)",  /* 139 */
        ":(7,*3,b9)",  /* 140 */
        ":(13,*3,b9)",  /* 141 */
        ":(7,*3,b9,13)",  /* 142 */
        ":(7,*3,b9,#11)",  /* 143 */
        ":(13,*3,b9,#11)",  /* 144 */
        ":(7,*3,b9,#11,b13)",  /* 145 */
        ":(7,*3,#9)",  /* 146 */
        ":(13,*3,#9)",  /* 147 */
        ":(7,*3,#9,b13)",  /* 148 */
        ":(9,*3,#11)",  /* 149 */
        ":(13,*3,#9,#11)",  /* 150 */
        ":(7,*3,#9,#11,b13)",  /* 151 */
        ":(7,*3,b5)",  /* 152 */
        ":(13,*3,b5)",  /* 153 */
        ":(7,*3,b5,b13)",  /* 154 */
        ":(9,*3,b5)",  /* 155 */
        ":(9,*3,b5,b13)",  /* 156 */
        ":(7,*3,b5,b9)",  /* 157 */
        ":(13,*3,b5,b9)",  /* 158 */
        ":(7,*3,b5,b9,b13)",  /* 159 */
        ":(7,*3,b5,#9)",  /* 160 */
        ":(13,*3,b5,#9)",  /* 161 */
        ":(7,*3,b5,#9,b13)",  /* 162 */
        ":(7,*3,#5)",  /* 163 */
        ":(13,*3,#5)",  /* 164 */
        ":(7,*3,#5,#11)",  /* 165 */
        ":(13,*3,#5,#11)",  /* 166 */
        ":(9,*3,#5)",  /* 167 */
        ":(9,*3,#5,#11)",  /* 168 */
        ":(7,*3,#5,b9)",  /* 169 */
        ":(13,*3,#5,b9)",  /* 170 */
        ":(7,*3,#5,b9,#11)",  /* 171 */
        ":(13,*3,#5,b9,#11)",  /* 172 */
        ":(7,*3,#5,#9)",  /* 173 */
        ":(13,*3,#5,#9,#11)",  /* 174 */
        ":(7,*3,#5,#9,#11)",  /* 175 */
        ":(13,*3,#5,#9,#11)",  /* 176 */
        ":(4)",  /* 177 */
        "?",  /* 178 */
        "?",  /* 179 */
        "?",  /* 180 */
        "?",  /* 181 */
        "?",  /* 182 */
        "?",  /* 183 */
        ":(*3)",  /* 184 */
        /* no chord names above 185 */
};

std::string name;
int meterNumerator;
int meterDenominator;
std::string key;
bool isMinor;
int tempo;
py::list py_list;


void OutputChord(int beat, int duration, const std::string &chord) {
    py::list chord_list;
    chord_list.append(beat);
    chord_list.append(duration);
    chord_list.append(chord);
    py_list.append(chord_list);
    // std::cout << "Beat = " << beat << " Duration = " << duration << " chord = " << chord << std::endl;
}

std::string ChordName(unsigned char root, unsigned char type) {
    int chordRoot = root % 18;
    int chordBass = (chordRoot - 1 + root / 18) % 12 + 1;

    if (chordRoot == chordBass)
        return std::string(rootNames[chordRoot - 1]) + std::string(harteNames[type - 1]);
    else
        return std::string(rootNames[chordRoot - 1]) + std::string(harteNames[type - 1]) + "/" +
               std::string(rootNames[chordBass - 1]);
}

void ReadBiaBFileNewFormat(std::ifstream &ifs) {
    unsigned char nameLen = ifs.get();
    char nameChars[nameLen];
    ifs.read(nameChars, nameLen);
    name = std::string(nameChars, nameLen);

    // Skip to byte denoting the style.
    ifs.get();
    ifs.get();
    unsigned char style = ifs.get();
    meterNumerator = (style == 8 || style == 17) ? 3 : 4;
    meterDenominator = 4;

    unsigned char songKey = ifs.get();
    if (songKey <= 17) {
        key = rootNames[songKey - 1];
        isMinor = false;
    } else {
        key = rootNames[songKey - 18];
        isMinor = true;
    }

    // Read tempo.
    unsigned char tempo1 = ifs.get();
    unsigned char tempo2 = ifs.get();
    tempo = tempo2 * 256 + tempo1;

    // This is the starting bar number.
    unsigned int bar = ifs.get();

    unsigned char types[1020];
    unsigned char roots[1020];
    unsigned int beats[1020];
    int numberOfChords = 0;

    // Maximum 255 bars!
    while (bar < 255) {
        unsigned char barType = ifs.get();
        if (barType == 0) {
            unsigned char duration = ifs.get();
            bar += duration;
        } else
            bar += 1;
    }

    unsigned int beat = 0;
    // Maximum 255 bars!
    while (beat < 1020) {
        unsigned char chordType = ifs.get();
        if (chordType == 0) {
            // handle rests (or more accurately: "space")
            unsigned char duration = ifs.get();
            beat += duration;
        } else {
            types[numberOfChords] = chordType;
            beats[numberOfChords] = beat;
            numberOfChords++;
            beat += 1;
        }
    }

    beat = 0;
    int i = 0;
    // Maximum 255 bars!
    while (beat < 1020) {
        unsigned char chordRoot = ifs.get();
        if (chordRoot == 0) {
            // handle rests (or more accurately: "space")
            unsigned char duration = ifs.get();
            beat += duration;
        } else {
            roots[i] = chordRoot;
            if (beat != beats[i])
                throw std::runtime_error("Inconsistent chord type and root beat");
            i++;
            beat += 1;
        }
    }

    if (i != numberOfChords)
        throw std::runtime_error("Inconsistent number of chord types and roots");

    for (int i = 0; i < numberOfChords - 1; i++)
        try {
            std::string chord = ChordName(roots[i], types[i]);
            int chordBeat = beats[i] * meterNumerator / meterDenominator;
            int chordDuration = (beats[i + 1] - beats[i]) * meterNumerator / meterDenominator;
            OutputChord(chordBeat, chordDuration, chord);
        }
        catch (std::exception &e) {
            throw std::runtime_error("Unrecognized chord: " + ChordName(roots[i], types[i]));
        }

    std::string chord = ChordName(roots[numberOfChords - 1], types[numberOfChords - 1]);
    OutputChord(beats[numberOfChords - 1] * meterNumerator / meterDenominator, meterNumerator, chord);
}

void ReadBiaBFileOldFormat(std::ifstream &ifs) {
    unsigned char nameLen = ifs.get();
    char nameChars[nameLen];
    ifs.read(nameChars, nameLen);
    name = std::string(nameChars, nameLen);

    // The byte denoting the style of the file is at position 0x3e
    ifs.seekg(0x3e);
    unsigned char style = ifs.get();
    meterNumerator = (style == 8 || style == 17) ? 3 : 4;
    meterDenominator = 4;

    unsigned char songKey = ifs.get();
    if (songKey <= 17) {
        key = rootNames[songKey - 1];
        isMinor = false;
    } else {
        key = rootNames[songKey - 18];
        isMinor = true;
    }

    // Read tempo.
    unsigned char tempo1 = ifs.get();
    unsigned char tempo2 = ifs.get();
    tempo = tempo2 * 256 + tempo1;

    // The chord types start at byte 0x82
    ifs.seekg(0x82);

    unsigned char types[256];
    unsigned char roots[256];
    unsigned int durations[256];

    for (int i = 0; i < 256; i++)
        types[i] = ifs.get();

    for (int i = 0; i < 256; i++)
        roots[i] = ifs.get();

    ifs.get();
    ifs.get();
    // This seems to be the length of the chorus (for determining the duration of the last chord).
    unsigned char chorusLength = ifs.get();

    for (int i = 0; i < chorusLength * 4; i++) {
        if (types[i] != 0) {
            unsigned int duration = 1;
            int j = i + 1;
            while (j < chorusLength * 4 && types[j] == 0) {
                j++;
                duration++;
            }
            durations[i] = duration;
        }
    }

    for (int i = 0; i < chorusLength * 4; i++)
        if (types[i] != 0)
            OutputChord(i, durations[i] * meterNumerator / meterDenominator, ChordName(roots[i], types[i]));
}

void ReadBiaBFile(std::basic_string<char, std::char_traits<char>, std::allocator<char>> filename) {
    std::ifstream ifs(filename);
    if (!ifs)
        throw std::runtime_error("Cannot open file to initialize chord sequence");

    unsigned char version = ifs.get();
    if (version == 0xbb || version == 0xbc)
        ReadBiaBFileOldFormat(ifs);
    else
        ReadBiaBFileNewFormat(ifs);

    // std::cout << std::endl;
    // std::cout << "Name = " << name << std::endl;
    // std::cout << "Meter = " << meterNumerator << "/" << meterDenominator << std::endl;
    // std::cout << "Key = " << key << (isMinor ? "m" : "") << std::endl;
    // std::cout << "Tempo = " << tempo << std::endl;
}

/*
 * Test iterating over all the files of the dataset
int main(int argc, char *argv[]) {
    int error = 0;
    int success = 0;
    string path = "/Users/andreapoltronieri/Downloads/BiabInternetCorpus2014-06-04/allBiabData";
    for (const auto &entry: fs::directory_iterator(path)) {
        try {
            ReadBiaBFile(entry.path());
            success++;
        }
        catch (std::exception &e) {
            error++;
            std::cout << "Exception: " << e.what() << std::endl;
        }
        std::cout << "Errors: " << (error) << "\nSuccess: " << success << std::endl;
    }
}*/


/*
void print(std::list<std::string> const &list)
{
    for (auto const &i: list) {
        std::cout << i << std::endl;
    }
}*/

py::list biab(std::string file_path) {
    try {
        ReadBiaBFile(file_path);
        // std::cout << "\n" << my_list.size() << std::endl;
    }
    catch (std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    PyThreadState* ts;

    return py_list;
}

PYBIND11_MODULE(biab_converter, handle) {
    handle.def("biab", &biab);
}
