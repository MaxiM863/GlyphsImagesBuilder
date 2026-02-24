#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <limits>
#include <map>
#include <filesystem>


#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../include/GIB.hpp"

namespace fs = std::filesystem;

// Utility function to clear input buffer
void clearInputBuffer() {
    std::cin.clear(); // Clear error flags
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
}

std::vector<std::string> splitString(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        tokens.push_back(item); // Keep empty tokens if delimiter repeats
    }

    return tokens;
}

std::string readFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return "";
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int get32HextiINT(const char* hexString) {

    unsigned int value = 0;
    
    int cntr = 0;

    while(hexString[cntr] != '\0' && cntr < 6) // Limit to 10 characters to prevent overflow{
    {
        char c = hexString[cntr];

        if(hexString[cntr] == 'U' || hexString[cntr] == '+')
        {
            cntr++;
            continue; // Stop if we reach the end of the string before processing 8 characters
        }
        value <<= 4; // Shift left by 4 bits to make room for the next hex digit
        
        if (c >= '0' && c <= '9') {
        
            value |= (c - '0'); // Convert character to integer and add to value
        } else if (c >= 'A' && c <= 'F') {
        
            value |= (c - 'A' + 10); // Convert character to integer and add to value
        } else if (c >= 'a' && c <= 'f') {
        
            value |= (c - 'a' + 10); // Convert character to integer and add to value
        } else {
        
            std::cerr << "Invalid hex character: " << c << "\n";
            return 0; // Return 0 or handle error as needed
        }

        cntr++;
    }

    return value;
}

std::vector<std::vector<Plage>> fontFilenames = {

                {                  
                    Plage("google.ttf", "Basic Latin", get32HextiINT("U+0"), get32HextiINT("U+7F")),
                    Plage("google.ttf", "Latin-1 Supplement", get32HextiINT("U+80"), get32HextiINT("U+FF")),
                    Plage("google.ttf", "Latin Extended-A", get32HextiINT("U+100"), get32HextiINT("U+17F")),
                    Plage("google.ttf", "Latin Extended-B", get32HextiINT("U+180"), get32HextiINT("U+24F")),            
                    Plage("google.ttf", "IPA Extensions", get32HextiINT("U+250"), get32HextiINT("U+2AF")),
                    Plage("google.ttf", "Spacing Modifier Letters", get32HextiINT("U+2B0"), get32HextiINT("U+2FF")),
                    Plage("google.ttf", "Combining Diacritical Marks", get32HextiINT("U+300"), get32HextiINT("U+36F")),
                    Plage("google.ttf", "Greek and Coptic", get32HextiINT("U+370"), get32HextiINT("U+3FF")),
                    Plage("google.ttf", "Cyrillic", get32HextiINT("U+400"), get32HextiINT("U+4FF")),
                    Plage("google.ttf", "Cyrillic Supplement", get32HextiINT("U+500"), get32HextiINT("U+527")),
                    Plage("google.ttf", "Armenian", get32HextiINT("U+531"), get32HextiINT("U+58A")),
                    Plage("google.ttf", "Hebrew", get32HextiINT("U+591"), get32HextiINT("U+5F4")),
                    Plage("google.ttf", "Arabic", get32HextiINT("U+600"), get32HextiINT("U+6FF")),
                    Plage("google.ttf", "Syriac", get32HextiINT("U+700"), get32HextiINT("U+74F")),
                    Plage("google.ttf", "Arabic Supplement", get32HextiINT("U+750"), get32HextiINT("U+77F")),
                    Plage("google.ttf", "Thaana", get32HextiINT("U+780"), get32HextiINT("U+7B1")),
                    Plage("google.ttf", "NKo", get32HextiINT("U+7C0"), get32HextiINT("U+7FA")),
                    Plage("google.ttf", "Samaritan", get32HextiINT("U+800"), get32HextiINT("U+83E")),
                    Plage("google.ttf", "Mandaic", get32HextiINT("U+840"), get32HextiINT("U+85E")),
                    Plage("google.ttf", "Devanagari", get32HextiINT("U+900"), get32HextiINT("U+97F")),
                    Plage("google.ttf", "Bengali", get32HextiINT("U+981"), get32HextiINT("U+9FB")),
                    Plage("google.ttf", "Gurmukhi", get32HextiINT("U+A01"), get32HextiINT("U+A75")),
                    Plage("google.ttf", "Gujarati", get32HextiINT("U+A81"), get32HextiINT("U+AF1")),
                    Plage("google.ttf", "Oriya", get32HextiINT("U+B01"), get32HextiINT("U+B77")),
                    Plage("google.ttf", "Tamil", get32HextiINT("U+B82"), get32HextiINT("U+BFA")),
                    Plage("google.ttf", "Telugu", get32HextiINT("U+C01"), get32HextiINT("U+C7F")),
                    Plage("google.ttf", "Kannada", get32HextiINT("U+C82"), get32HextiINT("U+CF2")),
                    Plage("google.ttf", "Malayalam", get32HextiINT("U+D02"), get32HextiINT("U+D7F")),
                    Plage("google.ttf", "Sinhala", get32HextiINT("U+D82"), get32HextiINT("U+DF4")),
                    Plage("google.ttf", "Thai", get32HextiINT("U+E01"), get32HextiINT("U+E5B")),
                    Plage("google.ttf", "Lao", get32HextiINT("U+E81"), get32HextiINT("U+EDD")),
                    Plage("google.ttf", "Tibetan", get32HextiINT("U+F00"), get32HextiINT("U+FDA")),
                    Plage("google.ttf", "Myanmar", get32HextiINT("U+1000"), get32HextiINT("U+109F")),
                    Plage("google.ttf", "Georgian", get32HextiINT("U+10A0"), get32HextiINT("U+10FC")),
                    Plage("google.ttf", "Hangul Jamo", get32HextiINT("U+1100"), get32HextiINT("U+11FF")),
                    Plage("google.ttf", "Ethiopic", get32HextiINT("U+1200"), get32HextiINT("U+137C")),
                    Plage("google.ttf", "Ethiopic Supplement", get32HextiINT("U+1380"), get32HextiINT("U+1399")),
                    Plage("google.ttf", "Cherokee", get32HextiINT("U+13A0"), get32HextiINT("U+13F4")),
                    Plage("google.ttf", "Unified Canadian Aboriginal Syllabics", get32HextiINT("U+1400"), get32HextiINT("U+167F")),
                    Plage("google.ttf", "Ogham", get32HextiINT("U+1680"), get32HextiINT("U+169C")),
                    Plage("google.ttf", "Runic", get32HextiINT("U+16A0"), get32HextiINT("U+16F0")),
                    Plage("google.ttf", "Tagalog", get32HextiINT("U+1700"), get32HextiINT("U+1714")),
                    Plage("google.ttf", "Hanunoo", get32HextiINT("U+1720"), get32HextiINT("U+1736")),
                    Plage("google.ttf", "Buhid", get32HextiINT("U+1740"), get32HextiINT("U+1753")),
                    Plage("google.ttf", "Tagbanwa", get32HextiINT("U+1760"), get32HextiINT("U+1773")),
                    Plage("google.ttf", "Khmer", get32HextiINT("U+1780"), get32HextiINT("U+17F9")),
                    Plage("google.ttf", "Mongolian", get32HextiINT("U+1800"), get32HextiINT("U+18AA")),
                    Plage("google.ttf", "Unified Canadian Aboriginal Syllabics Extended", get32HextiINT("U+18B0"), get32HextiINT("U+18F5")),
                    Plage("google.ttf", "Limbu", get32HextiINT("U+1900"), get32HextiINT("U+194F")),
                    Plage("google.ttf", "Tai Le", get32HextiINT("U+1950"), get32HextiINT("U+1974")),
                    Plage("google.ttf", "New Tai Lue", get32HextiINT("U+1980"), get32HextiINT("U+19DF")),
                    Plage("google.ttf", "Khmer Symbols", get32HextiINT("U+19E0"), get32HextiINT("U+19FF")),
                    Plage("google.ttf", "Buginese", get32HextiINT("U+1A00"), get32HextiINT("U+1A1F")),
                    Plage("google.ttf", "Tai Tham", get32HextiINT("U+1A20"), get32HextiINT("U+1AAD")),
                    Plage("google.ttf", "Balinese", get32HextiINT("U+1B00"), get32HextiINT("U+1B7C")),
                    Plage("google.ttf", "Sundanese", get32HextiINT("U+1B80"), get32HextiINT("U+1BB9")),
                    Plage("google.ttf", "Batak", get32HextiINT("U+1BC0"), get32HextiINT("U+1BFF")),
                    Plage("google.ttf", "Lepcha", get32HextiINT("U+1C00"), get32HextiINT("U+1C4F")),
                    Plage("google.ttf", "Ol Chiki", get32HextiINT("U+1C50"), get32HextiINT("U+1C7F")),
                    Plage("google.ttf", "Vedic Extensions", get32HextiINT("U+1CD0"), get32HextiINT("U+1CF2")),
                    Plage("google.ttf", "Phonetic Extensions", get32HextiINT("U+1D00"), get32HextiINT("U+1D7F")),
                    Plage("google.ttf", "Phonetic Extensions Supplement", get32HextiINT("U+1D80"), get32HextiINT("U+1DBF")),
                    Plage("google.ttf", "Combining Diacritical Marks Supplement", get32HextiINT("U+1DC0"), get32HextiINT("U+1DFF")),
                    Plage("google.ttf", "Latin Extended Additional", get32HextiINT("U+1E00"), get32HextiINT("U+1EFF")),
                    Plage("google.ttf", "Greek Extended", get32HextiINT("U+1F00"), get32HextiINT("U+1FFE")),
                    Plage("google.ttf", "General Punctuation", get32HextiINT("U+2000"), get32HextiINT("U+206F")),
                    Plage("google.ttf", "Superscripts and Subscripts", get32HextiINT("U+2070"), get32HextiINT("U+209C")),
                    Plage("google.ttf", "Currency Symbols", get32HextiINT("U+20A0"), get32HextiINT("U+20B9")),
                    Plage("google.ttf", "Combining Diacritical Marks for Symbols", get32HextiINT("U+20D0"), get32HextiINT("U+20F0")),
                    Plage("google.ttf", "Letterlike Symbols", get32HextiINT("U+2100"), get32HextiINT("U+214F")),
                    Plage("google.ttf", "Number Forms", get32HextiINT("U+2150"), get32HextiINT("U+2189")),
                    Plage("google.ttf", "Arrows", get32HextiINT("U+2190"), get32HextiINT("U+21FF")),
                    Plage("google.ttf", "Mathematical Operators", get32HextiINT("U+2200"), get32HextiINT("U+22FF")),
                    Plage("google.ttf", "Miscellaneous Technical", get32HextiINT("U+2300"), get32HextiINT("U+23F3")),
                    Plage("google.ttf", "Control Pictures", get32HextiINT("U+2400"), get32HextiINT("U+2426")),
                    Plage("google.ttf", "Optical Character Recognition", get32HextiINT("U+2440"), get32HextiINT("U+244A")),
                    Plage("google.ttf", "Enclosed Alphanumerics", get32HextiINT("U+2460"), get32HextiINT("U+24FF")),
                    Plage("google.ttf", "Box Drawing", get32HextiINT("U+2500"), get32HextiINT("U+257F")),
                    Plage("google.ttf", "Block Elements", get32HextiINT("U+2580"), get32HextiINT("U+259F")),
                    Plage("google.ttf", "Geometric Shapes", get32HextiINT("U+25A0"), get32HextiINT("U+25FF")),
                    Plage("google.ttf", "Miscellaneous Symbols", get32HextiINT("U+2600"), get32HextiINT("U+26FF")),
                    Plage("google.ttf", "Dingbats", get32HextiINT("U+2701"), get32HextiINT("U+27BF")),
                    Plage("google.ttf", "Miscellaneous Mathematical Symbols-A", get32HextiINT("U+27C0"), get32HextiINT("U+27EF")),
                    Plage("google.ttf", "Supplemental Arrows-A", get32HextiINT("U+27F0"), get32HextiINT("U+27FF")),
                    Plage("google.ttf", "Braille Patterns", get32HextiINT("U+2800"), get32HextiINT("U+28FF")),
                    Plage("google.ttf", "Supplemental Arrows-B", get32HextiINT("U+2900"), get32HextiINT("U+297F")),
                    Plage("google.ttf", "Miscellaneous Mathematical Symbols-B", get32HextiINT("U+2980"), get32HextiINT("U+29FF")),
                    Plage("google.ttf", "Supplemental Mathematical Operators", get32HextiINT("U+2A00"), get32HextiINT("U+2AFF")),
                    Plage("google.ttf", "Miscellaneous Symbols and Arrows", get32HextiINT("U+2B00"), get32HextiINT("U+2B59")),
                    Plage("google.ttf", "Glagolitic", get32HextiINT("U+2C00"), get32HextiINT("U+2C5E")),
                    Plage("google.ttf", "Latin Extended-C", get32HextiINT("U+2C60"), get32HextiINT("U+2C7F")),
                    Plage("google.ttf", "Coptic", get32HextiINT("U+2C80"), get32HextiINT("U+2CFF")),
                    Plage("google.ttf", "Georgian Supplement", get32HextiINT("U+2D00"), get32HextiINT("U+2D25")),
                    Plage("google.ttf", "Tifinagh", get32HextiINT("U+2D30"), get32HextiINT("U+2D7F")),
                    Plage("google.ttf", "Ethiopic Extended", get32HextiINT("U+2D80"), get32HextiINT("U+2DDE")),
                    Plage("google.ttf", "Cyrillic Extended-A", get32HextiINT("U+2DE0"), get32HextiINT("U+2DFF")),
                    Plage("google.ttf", "Supplemental Punctuation", get32HextiINT("U+2E00"), get32HextiINT("U+2E31")),
                    Plage("google.ttf", "Kangxi Radicals", get32HextiINT("U+2F00"), get32HextiINT("U+2FD5")),
                    Plage("google.ttf", "Ideographic Description Characters", get32HextiINT("U+2FF0"), get32HextiINT("U+2FFB")),                    
                    Plage("google.ttf", "Hiragana", get32HextiINT("U+3041"), get32HextiINT("U+309F")),
                    Plage("google.ttf", "Katakana", get32HextiINT("U+30A0"), get32HextiINT("U+30FF")),
                    Plage("google.ttf", "Bopomofo", get32HextiINT("U+3105"), get32HextiINT("U+312D")),
                    Plage("google.ttf", "Hangul Compatibility Jamo", get32HextiINT("U+3131"), get32HextiINT("U+318E")),
                    Plage("google.ttf", "Kanbun", get32HextiINT("U+3190"), get32HextiINT("U+319F")),
                    Plage("google.ttf", "Bopomofo Extended", get32HextiINT("U+31A0"), get32HextiINT("U+31BA")),                    
                    Plage("google.ttf", "Katakana Phonetic Extensions", get32HextiINT("U+31F0"), get32HextiINT("U+31FF")),
                    Plage("google.ttf", "Yijing Hexagram Symbols", get32HextiINT("U+4DC0"), get32HextiINT("U+4DFF")),
                    Plage("google.ttf", "Yi Syllables", get32HextiINT("U+A000"), get32HextiINT("U+A48C")),
                    Plage("google.ttf", "Yi Radicals", get32HextiINT("U+A490"), get32HextiINT("U+A4C6")),
                    Plage("google.ttf", "Lisu", get32HextiINT("U+A4D0"), get32HextiINT("U+A4FF")),
                    Plage("google.ttf", "Vai", get32HextiINT("U+A500"), get32HextiINT("U+A62B")),
                    Plage("google.ttf", "Cyrillic Extended-B", get32HextiINT("U+A640"), get32HextiINT("U+A697")),
                    Plage("google.ttf", "Bamum", get32HextiINT("U+A6A0"), get32HextiINT("U+A6F7")),
                    Plage("google.ttf", "Modifier Tone Letters", get32HextiINT("U+A700"), get32HextiINT("U+A71F")),
                    Plage("google.ttf", "Latin Extended-D", get32HextiINT("U+A720"), get32HextiINT("U+A7FF")),
                    Plage("google.ttf", "Syloti Nagri", get32HextiINT("U+A800"), get32HextiINT("U+A82B")),
                    Plage("google.ttf", "Common Indic Number Forms", get32HextiINT("U+A830"), get32HextiINT("U+A839")),
                    Plage("google.ttf", "Phags-pa", get32HextiINT("U+A840"), get32HextiINT("U+A877")),
                    Plage("google.ttf", "Saurashtra", get32HextiINT("U+A880"), get32HextiINT("U+A8D9")),
                    Plage("google.ttf", "Devanagari Extended", get32HextiINT("U+A8E0"), get32HextiINT("U+A8FB")),
                    Plage("google.ttf", "Kayah Li", get32HextiINT("U+A900"), get32HextiINT("U+A92F")),
                    Plage("google.ttf", "Rejang", get32HextiINT("U+A930"), get32HextiINT("U+A95F")),
                    Plage("google.ttf", "Hangul Jamo Extended-A", get32HextiINT("U+A960"), get32HextiINT("U+A97C")),
                    Plage("google.ttf", "Javanese", get32HextiINT("U+A980"), get32HextiINT("U+A9DF")),
                    Plage("google.ttf", "Cham", get32HextiINT("U+AA00"), get32HextiINT("U+AA5F")),
                    Plage("google.ttf", "Myanmar Extended-A", get32HextiINT("U+AA60"), get32HextiINT("U+AA7B")),
                    Plage("google.ttf", "Tai Viet", get32HextiINT("U+AA80"), get32HextiINT("U+AADF")),
                    Plage("google.ttf", "Ethiopic Extended-A", get32HextiINT("U+AB01"), get32HextiINT("U+AB2E")),
                    Plage("google.ttf", "Meetei Mayek", get32HextiINT("U+ABC0"), get32HextiINT("U+ABF9")),
                    Plage("google.ttf", "Hangul Syllables", get32HextiINT("U+AC00"), get32HextiINT("U+D7A3")),
                    Plage("google.ttf", "Hangul Jamo Extended-B", get32HextiINT("U+D7B0"), get32HextiINT("U+D7FB")),
                    Plage("google.ttf", "High Surrogates", get32HextiINT("U+D800"), get32HextiINT("U+DB7F")),
                    Plage("google.ttf", "High Private Use Surrogates", get32HextiINT("U+DB80"), get32HextiINT("U+DBFF")),
                    Plage("google.ttf", "Low Surrogates", get32HextiINT("U+DC00"), get32HextiINT("U+DFFF")),
                    Plage("google.ttf", "Private Use Area", get32HextiINT("U+E000"), get32HextiINT("U+F8FF")),                    
                    Plage("google.ttf", "Alphabetic Presentation Forms", get32HextiINT("U+FB00"), get32HextiINT("U+FB4F")),
                    Plage("google.ttf", "Arabic Presentation Forms-A", get32HextiINT("U+FB50"), get32HextiINT("U+FDFD")),
                    Plage("google.ttf", "Variation Selectors", get32HextiINT("U+FE00"), get32HextiINT("U+FE0F")),
                    Plage("google.ttf", "Vertical Forms", get32HextiINT("U+FE10"), get32HextiINT("U+FE19")),
                    Plage("google.ttf", "Combining Half Marks", get32HextiINT("U+FE20"), get32HextiINT("U+FE26")),
                    Plage("google.ttf", "Small Form Variants", get32HextiINT("U+FE50"), get32HextiINT("U+FE6B")),
                    Plage("google.ttf", "Arabic Presentation Forms-B", get32HextiINT("U+FE70"), get32HextiINT("U+FEFF")),
                    Plage("google.ttf", "Halfwidth and Fullwidth Forms", get32HextiINT("U+FF01"), get32HextiINT("U+FFEE")),
                    Plage("google.ttf", "Specials", get32HextiINT("U+FFF9"), get32HextiINT("U+FFFD"))
                    /*Plage("google.ttf", "Linear B Syllabary", get32HextiINT("U+10000"), get32HextiINT("U+1005D")),
                    Plage("google.ttf", "Linear B Ideograms", get32HextiINT("U+10080"), get32HextiINT("U+100FA")),
                    Plage("google.ttf", "Aegean Numbers", get32HextiINT("U+10100"), get32HextiINT("U+1013F")),
                    Plage("google.ttf", "Ancient Greek Numbers", get32HextiINT("U+10140"), get32HextiINT("U+1018A")),
                    Plage("google.ttf", "Ancient Symbols", get32HextiINT("U+10190"), get32HextiINT("U+1019B")),
                    Plage("google.ttf", "Phaistos Disc", get32HextiINT("U+101D0"), get32HextiINT("U+101FD")),
                    Plage("google.ttf", "Lycian", get32HextiINT("U+10280"), get32HextiINT("U+1029C")),
                    Plage("google.ttf", "Carian", get32HextiINT("U+102A0"), get32HextiINT("U+102D0")),
                    Plage("google.ttf", "Old Italic", get32HextiINT("U+10300"), get32HextiINT("U+10323")),
                    Plage("google.ttf", "Gothic", get32HextiINT("U+10330"), get32HextiINT("U+1034A")),
                    Plage("google.ttf", "Ugaritic", get32HextiINT("U+10380"), get32HextiINT("U+1039F")),
                    Plage("google.ttf", "Old Persian", get32HextiINT("U+103A0"), get32HextiINT("U+103D5")),
                    Plage("google.ttf", "Deseret", get32HextiINT("U+10400"), get32HextiINT("U+1044F")),
                    Plage("google.ttf", "Shavian", get32HextiINT("U+10450"), get32HextiINT("U+1047F")),
                    Plage("google.ttf", "Osmanya", get32HextiINT("U+10480"), get32HextiINT("U+104A9")),
                    Plage("google.ttf", "Cypriot Syllabary", get32HextiINT("U+10800"), get32HextiINT("U+1083F")),
                    Plage("google.ttf", "Imperial Aramaic", get32HextiINT("U+10840"), get32HextiINT("U+1085F")),
                    Plage("google.ttf", "Phoenician", get32HextiINT("U+10900"), get32HextiINT("U+1091F")),
                    Plage("google.ttf", "Lydian", get32HextiINT("U+10920"), get32HextiINT("U+1093F")),
                    Plage("google.ttf", "Kharoshthi", get32HextiINT("U+10A00"), get32HextiINT("U+10A58")),
                    Plage("google.ttf", "Old South Arabian", get32HextiINT("U+10A60"), get32HextiINT("U+10A7F")),
                    Plage("google.ttf", "Avestan", get32HextiINT("U+10B00"), get32HextiINT("U+10B3F")),
                    Plage("google.ttf", "Inscriptional Parthian", get32HextiINT("U+10B40"), get32HextiINT("U+10B5F")),
                    Plage("google.ttf", "Inscriptional Pahlavi", get32HextiINT("U+10B60"), get32HextiINT("U+10B7F")),
                    Plage("google.ttf", "Old Turkic", get32HextiINT("U+10C00"), get32HextiINT("U+10C48")),
                    Plage("google.ttf", "Rumi Numeral Symbols", get32HextiINT("U+10E60"), get32HextiINT("U+10E7E")),
                    Plage("google.ttf", "Brahmi", get32HextiINT("U+11000"), get32HextiINT("U+1106F")),
                    Plage("google.ttf", "Kaithi", get32HextiINT("U+11080"), get32HextiINT("U+110C1")),
                    Plage("google.ttf", "Cuneiform", get32HextiINT("U+12000"), get32HextiINT("U+1236E")),
                    Plage("google.ttf", "Cuneiform Numbers and Punctuation", get32HextiINT("U+12400"), get32HextiINT("U+12473")),
                    Plage("google.ttf", "Egyptian Hieroglyphs", get32HextiINT("U+13000"), get32HextiINT("U+1342E")),
                    Plage("google.ttf", "Bamum Supplement", get32HextiINT("U+16800"), get32HextiINT("U+16A38")),
                    Plage("google.ttf", "Kana Supplement", get32HextiINT("U+1B000"), get32HextiINT("U+1B001")),
                    Plage("google.ttf", "Byzantine Musical Symbols", get32HextiINT("U+1D000"), get32HextiINT("U+1D0F5")),
                    Plage("google.ttf", "Musical Symbols", get32HextiINT("U+1D100"), get32HextiINT("U+1D1DD")),
                    Plage("google.ttf", "Ancient Greek Musical Notation", get32HextiINT("U+1D200"), get32HextiINT("U+1D245")),
                    Plage("google.ttf", "Tai Xuan Jing Symbols", get32HextiINT("U+1D300"), get32HextiINT("U+1D356")),
                    Plage("google.ttf", "Counting Rod Numerals", get32HextiINT("U+1D360"), get32HextiINT("U+1D371")),
                    Plage("google.ttf", "Mathematical Alphanumeric Symbols", get32HextiINT("U+1D400"), get32HextiINT("U+1D7FF")),
                    Plage("google.ttf", "Mahjong Tiles", get32HextiINT("U+1F000"), get32HextiINT("U+1F02B")),
                    Plage("google.ttf", "Domino Tiles", get32HextiINT("U+1F030"), get32HextiINT("U+1F093")),
                    Plage("google.ttf", "Playing Cards", get32HextiINT("U+1F0A0"), get32HextiINT("U+1F0DF")),
                    Plage("google.ttf", "Enclosed Alphanumeric Supplement", get32HextiINT("U+1F100"), get32HextiINT("U+1F1FF")),
                    Plage("google.ttf", "Enclosed Ideographic Supplement", get32HextiINT("U+1F200"), get32HextiINT("U+1F251")),
                    Plage("google.ttf", "Miscellaneous Symbols And Pictographs", get32HextiINT("U+1F300"), get32HextiINT("U+1F5FF")),
                    Plage("google.ttf", "Emoticons", get32HextiINT("U+1F601"), get32HextiINT("U+1F64F")),
                    Plage("google.ttf", "Transport And Map Symbols", get32HextiINT("U+1F680"), get32HextiINT("U+1F6C5")),
                    Plage("google.ttf", "Alchemical Symbols", get32HextiINT("U+1F700"), get32HextiINT("U+1F773")),
                    Plage("google.ttf", "CJK Unified Ideographs Extension B", get32HextiINT("U+20000"), get32HextiINT("U+2A6D6")),
                    Plage("google.ttf", "CJK Unified Ideographs Extension C", get32HextiINT("U+2A700"), get32HextiINT("U+2B734")),
                    Plage("google.ttf", "CJK Unified Ideographs Extension D", get32HextiINT("U+2B740"), get32HextiINT("U+2B81D")),
                    Plage("google.ttf", "CJK Compatibility Ideographs Supplement", get32HextiINT("U+2F800"), get32HextiINT("U+2FA1D")),
                    Plage("google.ttf", "Tags", get32HextiINT("U+E0001"), get32HextiINT("U+E007F")),
                    Plage("google.ttf", "Variation Selectors Supplement", get32HextiINT("U+E0100"), get32HextiINT("U+E01EF")),
                    Plage("google.ttf", "Supplementary Private Use Area-A", get32HextiINT("U+F0000"), get32HextiINT("U+FFFFD")),
                    Plage("google.ttf", "Supplementary Private Use Area-B", get32HextiINT("U+100000"), get32HextiINT("U+10FFFD"))*/
                    },
                    {
                    Plage("china1.ttf", "CJK Strokes", get32HextiINT("U+31C0"), get32HextiINT("U+31E3")),    
                    Plage("china1.ttf", "CJK Symbols and Punctuation", get32HextiINT("U+3000"), get32HextiINT("U+303F")),
                    Plage("china1.ttf", "Enclosed CJK Letters and Months", get32HextiINT("U+3200"), get32HextiINT("U+32FE")),
                    Plage("china1.ttf", "CJK Compatibility", get32HextiINT("U+3300"), get32HextiINT("U+33FF")),
                    Plage("china1.ttf", "CJK Unified Ideographs Extension A", get32HextiINT("U+3400"), get32HextiINT("U+4DB5")),
                    Plage("china1.ttf", "CJK Unified Ideographs", get32HextiINT("U+4E00"), get32HextiINT("U+9FCB")),
                    Plage("china1.ttf", "CJK Compatibility Forms", get32HextiINT("U+FE30"), get32HextiINT("U+FE4F")),
                    Plage("china1.ttf", "CJK Compatibility Ideographs", get32HextiINT("U+F900"), get32HextiINT("U+FAD9")),
                    Plage("china1.ttf", "CJK Radicals Supplement", get32HextiINT("U+2E80"), get32HextiINT("U+2EF3"))
                    },
                    {
                    Plage("japan1.ttf", "CJK Strokes", get32HextiINT("U+31C0"), get32HextiINT("U+31E3")),
                    Plage("japan1.ttf", "CJK Symbols and Punctuation", get32HextiINT("U+3000"), get32HextiINT("U+303F")),
                    Plage("japan1.ttf", "Enclosed CJK Letters and Months", get32HextiINT("U+3200"), get32HextiINT("U+32FE"), 10000),
                    Plage("japan1.ttf", "CJK Compatibility", get32HextiINT("U+3300"), get32HextiINT("U+33FF"), 10000),
                    Plage("japan1.ttf", "CJK Unified Ideographs Extension A", get32HextiINT("U+3400"), get32HextiINT("U+4DB5"), 10000),
                    Plage("japan1.ttf", "CJK Unified Ideographs", get32HextiINT("U+4E00"), get32HextiINT("U+9FCB"), 10000),
                    Plage("japan1.ttf", "CJK Compatibility Forms", get32HextiINT("U+FE30"), get32HextiINT("U+FE4F"), 10000),
                    Plage("japan1.ttf", "CJK Compatibility Ideographs", get32HextiINT("U+F900"), get32HextiINT("U+FAD9"), 10000),
                    Plage("japan1.ttf", "CJK Radicals Supplement", get32HextiINT("U+2E80"), get32HextiINT("U+2EF3"), 10000)
                    },
                    {
                    Plage("korea.ttf", "CJK Strokes", get32HextiINT("U+31C0"), get32HextiINT("U+31E3")),    
                    Plage("korea.ttf", "CJK Symbols and Punctuation", get32HextiINT("U+3000"), get32HextiINT("U+303F")),
                    Plage("korea.ttf", "Enclosed CJK Letters and Months", get32HextiINT("U+3200"), get32HextiINT("U+32FE"), 20000),
                    Plage("korea.ttf", "CJK Compatibility", get32HextiINT("U+3300"), get32HextiINT("U+33FF"), 20000),
                    Plage("korea.ttf", "CJK Unified Ideographs Extension A", get32HextiINT("U+3400"), get32HextiINT("U+4DB5"), 20000),
                    Plage("korea.ttf", "CJK Unified Ideographs", get32HextiINT("U+4E00"), get32HextiINT("U+9FCB"), 20000),
                    Plage("korea.ttf", "CJK Compatibility Forms", get32HextiINT("U+FE30"), get32HextiINT("U+FE4F"), 20000),
                    Plage("korea.ttf", "CJK Compatibility Ideographs", get32HextiINT("U+F900"), get32HextiINT("U+FAD9"), 20000),
                    Plage("korea.ttf", "CJK Radicals Supplement", get32HextiINT("U+2E80"), get32HextiINT("U+2EF3"), 20000)
                    }
            };

            
            std::vector<std::string> getFilenamesInDirectory(const std::string& directory_path) {
                std::vector<std::string> filenames;
                try {
                    // Iterate over all entries in the directory (non-recursive)
                    for (const auto& entry : fs::directory_iterator(directory_path)) {
                        // Check if the entry is a regular file
                        if (fs::is_regular_file(entry.status())) {
                            // Get the filename and add it to the vector
                            filenames.push_back(entry.path().filename().string());
                        }
                    }
                } catch (const fs::filesystem_error& e) {
                    std::cerr << "Filesystem error: " << e.what() << std::endl;
                }
                return filenames;
            }



// Entry point of the program
int main() {

    std::string directoryPath = "./Fonts"; // Current directory for this example

    // Load the files
    std::vector<std::string> loadedFiles = getFilenamesInDirectory(directoryPath);

    
    bool test = false;

    for(int i =  0; i < 1; i++)
    {
        for(int j = 0; j < fontFilenames[i].size(); j++)
        {
        
            if(!GIB::isAllCaractersPresentInPlage(fontFilenames[i][j]))
            {

                bool test2 = false;

                for(int k = 0; k < loadedFiles.size(); k++)
                {
                    
                    fontFilenames[i][j].fontFilename = loadedFiles[k];

                    if(GIB::isAllCaractersPresentInPlage(fontFilenames[i][j]))
                    {
                        test2 = true;
                        std::cout << "*" ;
                        break;
                    }
                }

                if(!test2)
                {
                
                    fontFilenames[i][j].fontFilename = "google.ttf";
                }
                
                std::cout << "* " << fontFilenames[i][j].UnicodeName << " : " << fontFilenames[i][j].fontFilename << std::endl;
                

                test = true;
            }
            else std::cout << fontFilenames[i][j].UnicodeName << " : " << fontFilenames[i][j].fontFilename << std::endl;
        }
    }

    GIB::build(fontFilenames);

    std::cout << "=== Program Finished ===\n";
    return 0;
}
