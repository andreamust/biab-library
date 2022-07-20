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
#include <pybind11/stl.h>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

static const char *rootNames[] = {"C", "Db", "D", "Eb", "E", "F",
                                  "Gb", "G", "Ab", "A", "Bb", "B",
                                  "C#", "D#", "F#", "G#", "A#"};


static const char *harteNames[] = {
        ":maj",  /* 1 */
        ":maj",  /* 2 */
        ":(b5)",  /* 3 */
        ":aug",  /* 4 */
        ":(3,5,6)",  /* 5 */
        ":maj7",  /* 6 */
        ":maj9",  /* 7 */
        ":maj(7,9,#11)",  /* 8 */
        ":maj(7,9,13,#11)",  /* 9 */
        ":maj(7,9,11,13)",  /* 10 */
        ":(5,7,9)",  /* 11 */
        ":(3,#5)",  /* 12 */
        ":(3,#5,7)",  /* 13 */
        ":(3,5,6,9)",  /* 14 */
        ":(2,5)",  /* 15 */
        ":min",  /* 16 */
        ":min(#5)",  /* 17 */
        ":min(7)",  /* 18 */
        ":min(b7)",  /* 19 */
        ":min(b7,9)",  /* 20 */
        ":min(b7,9,11)",  /* 21 */
        ":min(b7,9,11,13)",  /* 22 */
        ":min(6)",  /* 23 */
        ":(b3,#5)",  /* 24 */
        ":(b3,#5,b7)",  /* 25 */
        ":(b3,5,6,9)",  /* 26 */
        "?",  /* 27 */
        "?",  /* 28 */
        "?",  /* 29 */
        "?",  /* 30 */
        "?",  /* 31 */
        ":(b3,b5,b7)",  /* 32 */
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
        ":(3,#5,b7)",  /* 56 */
        ":(3,#5,b7,9)",  /* 57 */
        ":(3,#5,b7,9,13)",  /* 58 */
        "?",  /* 59 */
        "?",  /* 60 */
        "?",  /* 61 */
        "?",  /* 62 */
        "?",  /* 63 */
        ":(3,5,b7)",  /* 64 */
        ":(3,5,b7,9,11,13)",  /* 65 */
        ":(3,5,b7,b13)",  /* 66 */
        ":(3,5,b7,#11)",  /* 67 */
        ":(3,5,b7,9,#11,13)",  /* 68 */
        ":(3,5,b7,#11,b13)",  /* 69 */
        ":(3,5,b7,9)",  /* 70 */
        "?",  /* 71 */
        ":(3,5,b7,9,b13)",  /* 72 */
        ":(3,5,b7,9,#11)",  /* 73 */
        ":(3,5,b7,9,#11,13)",  /* 74 */
        ":(3,5,b7,9,#11,b13)",  /* 75 */
        ":(3,5,b7,b9)",  /* 76 */
        ":(3,5,b7,b9,11,13)",  /* 77 */
        ":(3,5,b7,b9,b13)",  /* 78 */
        ":(3,5,b7,b9,#11)",  /* 79 */
        ":(3,5,b7,b9,#11,13)",  /* 80 */
        ":(3,5,b7,b9,#11,b13)",  /* 81 */
        ":(3,5,b7,#9)",  /* 82 */
        ":(3,5,b7,#9,11,13)",  /* 83 */
        ":(3,5,b7,#9,b13)",  /* 84 */
        ":(3,5,b7,9,#11)",  /* 85 */
        ":(3,5,b7,#9,#11,13)",  /* 86 */
        ":(3,5,b7,#9,#11,b13)",  /* 87 */
        ":(3,b5,b7)",  /* 88 */
        ":(3,b5,b7,9,11,13)",  /* 89 */
        ":(3,b5,b7,b13)",  /* 90 */
        ":(3,b5,b7,b9)",  /* 91 */
        ":(3,b5,b7,9,b13)",  /* 92 */
        ":(3,b5,b7,b9)",  /* 93 */
        ":(3,b5,b7,b9,11,13)",  /* 94 */
        ":(3,b5,b7,b9,b13)",  /* 95 */
        ":(3,b5,b7,#9)",  /* 96 */
        ":(3,b5,b7,#9,13)",  /* 97 */
        ":(3,b5,b7,#9,b13)",  /* 98 */
        ":(3,#5,b7)",  /* 99 */
        ":(3,#5,b7,9,11,13)",  /* 100 */
        ":(3,#5,b7,#11)",  /* 101 */
        ":(3,#5,b7,9,#11,13)",  /* 102 */
        ":(3,#5,b7,9)",  /* 103 */
        ":(3,#5,b7,9,#11)",  /* 104 */
        ":(3,#5,b7,b9)",  /* 105 */
        ":(3,#5,b7,b9,11,13)",  /* 106 */
        ":(3,#5,b7,b9,#11)",  /* 107 */
        ":(3,#5,b7,b9,#11,13)",  /* 108 */
        ":(3,#5,b7,#9)",  /* 109 */
        ":(3,#5,b7,#9,#11,13)",  /* 110 */
        ":(3,#5,b7,#9,#11)",  /* 111 */
        ":(3,#5,b7,#9,#11,13)",  /* 112 */
        ":(3,b5,#5,b7,b9,#9)",  /* 113 */
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
        ":(4,5,b7)",  /* 128 */
        ":(4,5,b7,9,11,13)",  /* 129 */
        ":(4,5,b7,b13)",  /* 130 */
        ":(4,5,b7,#11)",  /* 131 */
        ":(4,5,b7,9,#11,13)",  /* 132 */
        ":(4,5,b7,#11,b13)",  /* 133 */
        ":(4,5,b7,9)",  /* 134 */
        "?",  /* 135 */
        ":(4,5,b7,9,b13)",  /* 136 */
        ":(4,5,b7,9,#11)",  /* 137 */
        ":(4,5,b7,9,#11,13)",  /* 138 */
        ":(4,5,b7,9,#11,b13)",  /* 139 */
        ":(4,5,b7,b9)",  /* 140 */
        ":(4,5,b7,b9,11,13)",  /* 141 */
        ":(4,5,b7,b9,13)",  /* 142 */
        ":(4,5,b7,b9,#11)",  /* 143 */
        ":(4,5,b7,b9,#11,13)",  /* 144 */
        ":(4,5,b7,b9,#11,b13)",  /* 145 */
        ":(4,5,b7,#9)",  /* 146 */
        ":(4,5,b7,#9,11,13)",  /* 147 */
        ":(4,5,b7,#9,b13)",  /* 148 */
        ":(4,5,b7,9,#11)",  /* 149 */
        ":(4,5,b7,#9,#11,13)",  /* 150 */
        ":(4,5,b7,#9,#11,b13)",  /* 151 */
        ":(4,b5,b7)",  /* 152 */
        ":(4,b5,b7,9,11,13)",  /* 153 */
        ":(4,b5,b7,b13)",  /* 154 */
        ":(4,b5,b7,9)",  /* 155 */
        ":(4,b5,b7,9,b13)",  /* 156 */
        ":(4,b5,b7,b9)",  /* 157 */
        ":(4,b5,b7,b9,11,13)",  /* 158 */
        ":(4,b5,b7,b9,b13)",  /* 159 */
        ":(4,b5,b7,#9)",  /* 160 */
        ":(4,b5,b7,#9,11,13)",  /* 161 */
        ":(4,b5,b7,#9,b13)",  /* 162 */
        ":(4,#5,b7)",  /* 163 */
        ":(4,#5,b7,9,11,13)",  /* 164 */
        ":(4,#5,b7,#11)",  /* 165 */
        ":(4,#5,b7,9,#11,13)",  /* 166 */
        ":(4,#5,b7,9)",  /* 167 */
        ":(4,#5,b7,9,#11)",  /* 168 */
        ":(4,#5,b7,b9)",  /* 169 */
        ":(4,#5,b7,b9,11,13)",  /* 170 */
        ":(4,#5,b7,b9,#11)",  /* 171 */
        ":(4,#5,b7,b9,#11,13)",  /* 172 */
        ":(4,#5,b7,#9)",  /* 173 */
        ":(4,#5,b7,#9,#11,13)",  /* 174 */
        ":(4,#5,b7,#9,#11)",  /* 175 */
        ":(4,#5,b7,#9,#11,13)",  /* 176 */
        ":(4)",  /* 177 */
        "?",  /* 178 */
        "?",  /* 179 */
        "?",  /* 180 */
        "?",  /* 181 */
        "?",  /* 182 */
        "?",  /* 183 */
        ":(4,5)",  /* 184 */
        /* no chord names above 185 */
};

std::string name;
int meterNumerator;
int meterDenominator;
std::string key;
bool isMinor;
int tempo;
std::vector<std::vector<std::string>> chord_list{};
std::vector<std::string> meta_list{};


void OutputChord(int beat, int duration, const std::string &chord) {
    std::vector<std::string> this_chord_list;
    this_chord_list.push_back(std::to_string(beat));
    this_chord_list.push_back(std::to_string(duration));
    this_chord_list.push_back(chord);
    chord_list.push_back(this_chord_list);
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
            OutputChord(i, durations[i] * meterNumerator / meterDenominator,
                        ChordName(roots[i], types[i]));
}

void ReadBiaBFile(std::basic_string<char, std::char_traits<char>, std::allocator<char>> filename) {
    chord_list = {};
    meta_list = {};
    std::ifstream ifs(filename);
    if (!ifs)
        throw std::runtime_error("Cannot open file to initialize chord sequence");

    unsigned char version = ifs.get();
    if (version == 0xbb || version == 0xbc)
        ReadBiaBFileOldFormat(ifs);
    else
        ReadBiaBFileNewFormat(ifs);
    meta_list.push_back(name);
    meta_list.push_back(std::to_string(meterNumerator));
    meta_list.push_back(std::to_string(meterDenominator));
    meta_list.push_back(key);
    meta_list.push_back(std::to_string(tempo));
//    std::cout << std::endl;
//    std::cout << "Name = " << name << std::endl;
//    std::cout << "Meter = " << meterNumerator << "/" << meterDenominator << std::endl;
//    std::cout << "Key = " << key << (isMinor ? "m" : "") << std::endl;
//    std::cout << "Tempo = " << tempo << std::endl;
}

std::tuple<std::vector<std::string>, std::vector<std::vector<std::string>>> biab_data(std::string file_path) {
try {
ReadBiaBFile(file_path);
// std::cout << "\n" << my_list.size() << std::endl;
}
catch (std::exception &e) {
std::cout << "Exception: " << e.what() << std::endl;
}

return {meta_list, chord_list};
}

std::vector<std::vector<std::string>> biab_chords(std::string file_path) {
    try {
        ReadBiaBFile(file_path);
        // std::cout << "\n" << my_list.size() << std::endl;
    }
    catch (std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return chord_list;
}

std::vector<std::string> biab_meta(std::string file_path) {
    try {
        ReadBiaBFile(file_path);
        // std::cout << "\n" << my_list.size() << std::endl;
    }
    catch (std::exception &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return meta_list;
}

PYBIND11_MODULE(biab, handle) {
handle.doc() = "Function for opening and managing Band-in-a-Box files. The function takes as input a file path of"
               "a BIAB file and returns a tuple of list, where the first list contains metadata about the track, "
               "while the second contains chords information.";
handle.def("biab_data", &biab_data, R"pbdoc(
        Returns all available data from the BIAB file, including metadata and chord annotation.
    )pbdoc");
handle.def("biab_meta", &biab_meta, R"pbdoc(
        Returns metadata information from the BIAB file.
    )pbdoc");
handle.def("biab_chords", &biab_chords, R"pbdoc(
        Returns chord annotations from the BIAB file.
    )pbdoc");
#ifdef VERSION_INFO
handle.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
handle.attr("__version__") = "dev";
#endif
}
