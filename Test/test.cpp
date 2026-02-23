#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <limits>


#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../include/GIB.hpp"

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
                    Plage("max.ttf", "IPA Extensions", get32HextiINT("U+250"), get32HextiINT("U+2AF")),
                    Plage("max.ttf", "Spacing Modifier Letters", get32HextiINT("U+2B0"), get32HextiINT("U+2FF")),
                    Plage("max.ttf", "Combining Diacritical Marks", get32HextiINT("U+300"), get32HextiINT("U+36F")),
                    Plage("max.ttf", "Greek and Coptic", get32HextiINT("U+370"), get32HextiINT("U+3FF")),
                    Plage("max.ttf", "Cyrillic", get32HextiINT("U+400"), get32HextiINT("U+4FF")),
                    Plage("max.ttf", "Cyrillic Supplement", get32HextiINT("U+500"), get32HextiINT("U+527")),
                    Plage("max.ttf", "Armenian", get32HextiINT("U+531"), get32HextiINT("U+58A")),
                    Plage("max.ttf", "Hebrew", get32HextiINT("U+591"), get32HextiINT("U+5F4")),
                    Plage("max.ttf", "Arabic", get32HextiINT("U+600"), get32HextiINT("U+6FF")),
                    Plage("max.ttf", "Syriac", get32HextiINT("U+700"), get32HextiINT("U+74F")),
                    Plage("max.ttf", "Arabic Supplement", get32HextiINT("U+750"), get32HextiINT("U+77F")),
                    Plage("max.ttf", "Thaana", get32HextiINT("U+780"), get32HextiINT("U+7B1")),
                    Plage("max.ttf", "NKo", get32HextiINT("U+7C0"), get32HextiINT("U+7FA")),
                    Plage("max.ttf", "Samaritan", get32HextiINT("U+800"), get32HextiINT("U+83E")),
                    Plage("max.ttf", "Mandaic", get32HextiINT("U+840"), get32HextiINT("U+85E")),
                    Plage("max.ttf", "Devanagari", get32HextiINT("U+900"), get32HextiINT("U+97F")),
                    Plage("max.ttf", "Bengali", get32HextiINT("U+981"), get32HextiINT("U+9FB")),
                    Plage("max.ttf", "Gurmukhi", get32HextiINT("U+A01"), get32HextiINT("U+A75")),
                    Plage("max.ttf", "Gujarati", get32HextiINT("U+A81"), get32HextiINT("U+AF1")),
                    Plage("max.ttf", "Oriya", get32HextiINT("U+B01"), get32HextiINT("U+B77")),
                    Plage("max.ttf", "Tamil", get32HextiINT("U+B82"), get32HextiINT("U+BFA")),
                    Plage("max.ttf", "Telugu", get32HextiINT("U+C01"), get32HextiINT("U+C7F")),
                    Plage("max.ttf", "Kannada", get32HextiINT("U+C82"), get32HextiINT("U+CF2")),
                    Plage("max.ttf", "Malayalam", get32HextiINT("U+D02"), get32HextiINT("U+D7F")),
                    Plage("max.ttf", "Sinhala", get32HextiINT("U+D82"), get32HextiINT("U+DF4")),
                    Plage("max.ttf", "Thai", get32HextiINT("U+E01"), get32HextiINT("U+E5B")),
                    Plage("max.ttf", "Lao", get32HextiINT("U+E81"), get32HextiINT("U+EDD")),
                    Plage("max.ttf", "Tibetan", get32HextiINT("U+F00"), get32HextiINT("U+FDA")),
                    Plage("max.ttf", "Myanmar", get32HextiINT("U+1000"), get32HextiINT("U+109F")),
                    Plage("max.ttf", "Georgian", get32HextiINT("U+10A0"), get32HextiINT("U+10FC")),
                    Plage("max.ttf", "Hangul Jamo", get32HextiINT("U+1100"), get32HextiINT("U+11FF")),
                    Plage("max.ttf", "Ethiopic", get32HextiINT("U+1200"), get32HextiINT("U+137C")),
                    Plage("max.ttf", "Ethiopic Supplement", get32HextiINT("U+1380"), get32HextiINT("U+1399")),
                    Plage("max.ttf", "Cherokee", get32HextiINT("U+13A0"), get32HextiINT("U+13F4")),
                    Plage("max.ttf", "Unified Canadian Aboriginal Syllabics", get32HextiINT("U+1400"), get32HextiINT("U+167F")),
                    Plage("max.ttf", "Ogham", get32HextiINT("U+1680"), get32HextiINT("U+169C")),
                    Plage("max.ttf", "Runic", get32HextiINT("U+16A0"), get32HextiINT("U+16F0")),
                    Plage("max.ttf", "Tagalog", get32HextiINT("U+1700"), get32HextiINT("U+1714")),
                    Plage("max.ttf", "Hanunoo", get32HextiINT("U+1720"), get32HextiINT("U+1736")),
                    Plage("max.ttf", "Buhid", get32HextiINT("U+1740"), get32HextiINT("U+1753")),
                    Plage("max.ttf", "Tagbanwa", get32HextiINT("U+1760"), get32HextiINT("U+1773")),
                    Plage("max.ttf", "Khmer", get32HextiINT("U+1780"), get32HextiINT("U+17F9")),
                    Plage("max.ttf", "Mongolian", get32HextiINT("U+1800"), get32HextiINT("U+18AA")),
                    Plage("max.ttf", "Unified Canadian Aboriginal Syllabics Extended", get32HextiINT("U+18B0"), get32HextiINT("U+18F5")),
                    Plage("max.ttf", "Limbu", get32HextiINT("U+1900"), get32HextiINT("U+194F")),
                    Plage("max.ttf", "Tai Le", get32HextiINT("U+1950"), get32HextiINT("U+1974")),
                    Plage("max.ttf", "New Tai Lue", get32HextiINT("U+1980"), get32HextiINT("U+19DF")),
                    Plage("max.ttf", "Khmer Symbols", get32HextiINT("U+19E0"), get32HextiINT("U+19FF")),
                    Plage("max.ttf", "Buginese", get32HextiINT("U+1A00"), get32HextiINT("U+1A1F")),
                    Plage("max.ttf", "Tai Tham", get32HextiINT("U+1A20"), get32HextiINT("U+1AAD")),
                    Plage("max.ttf", "Balinese", get32HextiINT("U+1B00"), get32HextiINT("U+1B7C")),
                    Plage("max.ttf", "Sundanese", get32HextiINT("U+1B80"), get32HextiINT("U+1BB9")),
                    Plage("max.ttf", "Batak", get32HextiINT("U+1BC0"), get32HextiINT("U+1BFF")),
                    Plage("max.ttf", "Lepcha", get32HextiINT("U+1C00"), get32HextiINT("U+1C4F")),
                    Plage("max.ttf", "Ol Chiki", get32HextiINT("U+1C50"), get32HextiINT("U+1C7F")),
                    Plage("max.ttf", "Vedic Extensions", get32HextiINT("U+1CD0"), get32HextiINT("U+1CF2")),
                    Plage("max.ttf", "Phonetic Extensions", get32HextiINT("U+1D00"), get32HextiINT("U+1D7F")),
                    Plage("max.ttf", "Phonetic Extensions Supplement", get32HextiINT("U+1D80"), get32HextiINT("U+1DBF")),
                    Plage("max.ttf", "Combining Diacritical Marks Supplement", get32HextiINT("U+1DC0"), get32HextiINT("U+1DFF")),
                    Plage("max.ttf", "Latin Extended Additional", get32HextiINT("U+1E00"), get32HextiINT("U+1EFF")),
                    Plage("max.ttf", "Greek Extended", get32HextiINT("U+1F00"), get32HextiINT("U+1FFE")),
                    Plage("max.ttf", "General Punctuation", get32HextiINT("U+2000"), get32HextiINT("U+206F")),
                    Plage("max.ttf", "Superscripts and Subscripts", get32HextiINT("U+2070"), get32HextiINT("U+209C")),
                    Plage("max.ttf", "Currency Symbols", get32HextiINT("U+20A0"), get32HextiINT("U+20B9")),
                    Plage("max.ttf", "Combining Diacritical Marks for Symbols", get32HextiINT("U+20D0"), get32HextiINT("U+20F0")),
                    Plage("max.ttf", "Letterlike Symbols", get32HextiINT("U+2100"), get32HextiINT("U+214F")),
                    Plage("max.ttf", "Number Forms", get32HextiINT("U+2150"), get32HextiINT("U+2189")),
                    Plage("max.ttf", "Arrows", get32HextiINT("U+2190"), get32HextiINT("U+21FF")),
                    Plage("max.ttf", "Mathematical Operators", get32HextiINT("U+2200"), get32HextiINT("U+22FF")),
                    Plage("max.ttf", "Miscellaneous Technical", get32HextiINT("U+2300"), get32HextiINT("U+23F3")),
                    Plage("max.ttf", "Control Pictures", get32HextiINT("U+2400"), get32HextiINT("U+2426")),
                    Plage("max.ttf", "Optical Character Recognition", get32HextiINT("U+2440"), get32HextiINT("U+244A")),
                    Plage("max.ttf", "Enclosed Alphanumerics", get32HextiINT("U+2460"), get32HextiINT("U+24FF")),
                    Plage("max.ttf", "Box Drawing", get32HextiINT("U+2500"), get32HextiINT("U+257F")),
                    Plage("max.ttf", "Block Elements", get32HextiINT("U+2580"), get32HextiINT("U+259F")),
                    Plage("max.ttf", "Geometric Shapes", get32HextiINT("U+25A0"), get32HextiINT("U+25FF")),
                    Plage("max.ttf", "Miscellaneous Symbols", get32HextiINT("U+2600"), get32HextiINT("U+26FF")),
                    Plage("max.ttf", "Dingbats", get32HextiINT("U+2701"), get32HextiINT("U+27BF")),
                    Plage("max.ttf", "Miscellaneous Mathematical Symbols-A", get32HextiINT("U+27C0"), get32HextiINT("U+27EF")),
                    Plage("max.ttf", "Supplemental Arrows-A", get32HextiINT("U+27F0"), get32HextiINT("U+27FF")),
                    Plage("max.ttf", "Braille Patterns", get32HextiINT("U+2800"), get32HextiINT("U+28FF")),
                    Plage("max.ttf", "Supplemental Arrows-B", get32HextiINT("U+2900"), get32HextiINT("U+297F")),
                    Plage("max.ttf", "Miscellaneous Mathematical Symbols-B", get32HextiINT("U+2980"), get32HextiINT("U+29FF")),
                    Plage("max.ttf", "Supplemental Mathematical Operators", get32HextiINT("U+2A00"), get32HextiINT("U+2AFF")),
                    Plage("max.ttf", "Miscellaneous Symbols and Arrows", get32HextiINT("U+2B00"), get32HextiINT("U+2B59")),
                    Plage("max.ttf", "Glagolitic", get32HextiINT("U+2C00"), get32HextiINT("U+2C5E")),
                    Plage("max.ttf", "Latin Extended-C", get32HextiINT("U+2C60"), get32HextiINT("U+2C7F")),
                    Plage("max.ttf", "Coptic", get32HextiINT("U+2C80"), get32HextiINT("U+2CFF")),
                    Plage("max.ttf", "Georgian Supplement", get32HextiINT("U+2D00"), get32HextiINT("U+2D25")),
                    Plage("max.ttf", "Tifinagh", get32HextiINT("U+2D30"), get32HextiINT("U+2D7F")),
                    Plage("max.ttf", "Ethiopic Extended", get32HextiINT("U+2D80"), get32HextiINT("U+2DDE")),
                    Plage("max.ttf", "Cyrillic Extended-A", get32HextiINT("U+2DE0"), get32HextiINT("U+2DFF")),
                    Plage("max.ttf", "Supplemental Punctuation", get32HextiINT("U+2E00"), get32HextiINT("U+2E31")),
                    Plage("max.ttf", "Kangxi Radicals", get32HextiINT("U+2F00"), get32HextiINT("U+2FD5")),
                    Plage("max.ttf", "Ideographic Description Characters", get32HextiINT("U+2FF0"), get32HextiINT("U+2FFB")),
                    Plage("max.ttf", "CJK Symbols and Punctuation", get32HextiINT("U+3000"), get32HextiINT("U+303F")),
                    Plage("max.ttf", "Hiragana", get32HextiINT("U+3041"), get32HextiINT("U+309F")),
                    Plage("max.ttf", "Katakana", get32HextiINT("U+30A0"), get32HextiINT("U+30FF")),
                    Plage("max.ttf", "Bopomofo", get32HextiINT("U+3105"), get32HextiINT("U+312D")),
                    Plage("max.ttf", "Hangul Compatibility Jamo", get32HextiINT("U+3131"), get32HextiINT("U+318E")),
                    Plage("max.ttf", "Kanbun", get32HextiINT("U+3190"), get32HextiINT("U+319F")),
                    Plage("max.ttf", "Bopomofo Extended", get32HextiINT("U+31A0"), get32HextiINT("U+31BA")),
                    Plage("max.ttf", "CJK Strokes", get32HextiINT("U+31C0"), get32HextiINT("U+31E3")),
                    Plage("max.ttf", "Katakana Phonetic Extensions", get32HextiINT("U+31F0"), get32HextiINT("U+31FF")),
                    Plage("max.ttf", "Yijing Hexagram Symbols", get32HextiINT("U+4DC0"), get32HextiINT("U+4DFF")),
                    Plage("max.ttf", "Yi Syllables", get32HextiINT("U+A000"), get32HextiINT("U+A48C")),
                    Plage("max.ttf", "Yi Radicals", get32HextiINT("U+A490"), get32HextiINT("U+A4C6")),
                    Plage("max.ttf", "Lisu", get32HextiINT("U+A4D0"), get32HextiINT("U+A4FF")),
                    Plage("max.ttf", "Vai", get32HextiINT("U+A500"), get32HextiINT("U+A62B")),
                    Plage("max.ttf", "Cyrillic Extended-B", get32HextiINT("U+A640"), get32HextiINT("U+A697")),
                    Plage("max.ttf", "Bamum", get32HextiINT("U+A6A0"), get32HextiINT("U+A6F7")),
                    Plage("max.ttf", "Modifier Tone Letters", get32HextiINT("U+A700"), get32HextiINT("U+A71F")),
                    Plage("max.ttf", "Latin Extended-D", get32HextiINT("U+A720"), get32HextiINT("U+A7FF")),
                    Plage("max.ttf", "Syloti Nagri", get32HextiINT("U+A800"), get32HextiINT("U+A82B")),
                    Plage("max.ttf", "Common Indic Number Forms", get32HextiINT("U+A830"), get32HextiINT("U+A839")),
                    Plage("max.ttf", "Phags-pa", get32HextiINT("U+A840"), get32HextiINT("U+A877")),
                    Plage("max.ttf", "Saurashtra", get32HextiINT("U+A880"), get32HextiINT("U+A8D9")),
                    Plage("max.ttf", "Devanagari Extended", get32HextiINT("U+A8E0"), get32HextiINT("U+A8FB")),
                    Plage("max.ttf", "Kayah Li", get32HextiINT("U+A900"), get32HextiINT("U+A92F")),
                    Plage("max.ttf", "Rejang", get32HextiINT("U+A930"), get32HextiINT("U+A95F")),
                    Plage("max.ttf", "Hangul Jamo Extended-A", get32HextiINT("U+A960"), get32HextiINT("U+A97C")),
                    Plage("max.ttf", "Javanese", get32HextiINT("U+A980"), get32HextiINT("U+A9DF")),
                    Plage("max.ttf", "Cham", get32HextiINT("U+AA00"), get32HextiINT("U+AA5F")),
                    Plage("max.ttf", "Myanmar Extended-A", get32HextiINT("U+AA60"), get32HextiINT("U+AA7B")),
                    Plage("max.ttf", "Tai Viet", get32HextiINT("U+AA80"), get32HextiINT("U+AADF")),
                    Plage("max.ttf", "Ethiopic Extended-A", get32HextiINT("U+AB01"), get32HextiINT("U+AB2E")),
                    Plage("max.ttf", "Meetei Mayek", get32HextiINT("U+ABC0"), get32HextiINT("U+ABF9")),
                    Plage("max.ttf", "Hangul Syllables", get32HextiINT("U+AC00"), get32HextiINT("U+D7A3")),
                    Plage("max.ttf", "Hangul Jamo Extended-B", get32HextiINT("U+D7B0"), get32HextiINT("U+D7FB")),
                    Plage("max.ttf", "High Surrogates", get32HextiINT("U+D800"), get32HextiINT("U+DB7F")),
                    Plage("max.ttf", "High Private Use Surrogates", get32HextiINT("U+DB80"), get32HextiINT("U+DBFF")),
                    Plage("max.ttf", "Low Surrogates", get32HextiINT("U+DC00"), get32HextiINT("U+DFFF")),
                    Plage("max.ttf", "Private Use Area", get32HextiINT("U+E000"), get32HextiINT("U+F8FF")),                    
                    Plage("max.ttf", "Alphabetic Presentation Forms", get32HextiINT("U+FB00"), get32HextiINT("U+FB4F")),
                    Plage("max.ttf", "Arabic Presentation Forms-A", get32HextiINT("U+FB50"), get32HextiINT("U+FDFD")),
                    Plage("max.ttf", "Variation Selectors", get32HextiINT("U+FE00"), get32HextiINT("U+FE0F")),
                    Plage("max.ttf", "Vertical Forms", get32HextiINT("U+FE10"), get32HextiINT("U+FE19")),
                    Plage("max.ttf", "Combining Half Marks", get32HextiINT("U+FE20"), get32HextiINT("U+FE26")),
                    Plage("max.ttf", "Small Form Variants", get32HextiINT("U+FE50"), get32HextiINT("U+FE6B")),
                    Plage("max.ttf", "Arabic Presentation Forms-B", get32HextiINT("U+FE70"), get32HextiINT("U+FEFF")),
                    Plage("max.ttf", "Halfwidth and Fullwidth Forms", get32HextiINT("U+FF01"), get32HextiINT("U+FFEE")),
                    Plage("max.ttf", "Specials", get32HextiINT("U+FFF9"), get32HextiINT("U+FFFD")),
                    /*Plage("max.ttf", "Linear B Syllabary", get32HextiINT("U+10000"), get32HextiINT("U+1005D")),
                    Plage("max.ttf", "Linear B Ideograms", get32HextiINT("U+10080"), get32HextiINT("U+100FA")),
                    Plage("max.ttf", "Aegean Numbers", get32HextiINT("U+10100"), get32HextiINT("U+1013F")),
                    Plage("max.ttf", "Ancient Greek Numbers", get32HextiINT("U+10140"), get32HextiINT("U+1018A")),
                    Plage("max.ttf", "Ancient Symbols", get32HextiINT("U+10190"), get32HextiINT("U+1019B")),
                    Plage("max.ttf", "Phaistos Disc", get32HextiINT("U+101D0"), get32HextiINT("U+101FD")),
                    Plage("max.ttf", "Lycian", get32HextiINT("U+10280"), get32HextiINT("U+1029C")),
                    Plage("max.ttf", "Carian", get32HextiINT("U+102A0"), get32HextiINT("U+102D0")),
                    Plage("max.ttf", "Old Italic", get32HextiINT("U+10300"), get32HextiINT("U+10323")),
                    Plage("max.ttf", "Gothic", get32HextiINT("U+10330"), get32HextiINT("U+1034A")),
                    Plage("max.ttf", "Ugaritic", get32HextiINT("U+10380"), get32HextiINT("U+1039F")),
                    Plage("max.ttf", "Old Persian", get32HextiINT("U+103A0"), get32HextiINT("U+103D5")),
                    Plage("max.ttf", "Deseret", get32HextiINT("U+10400"), get32HextiINT("U+1044F")),
                    Plage("max.ttf", "Shavian", get32HextiINT("U+10450"), get32HextiINT("U+1047F")),
                    Plage("max.ttf", "Osmanya", get32HextiINT("U+10480"), get32HextiINT("U+104A9")),
                    Plage("max.ttf", "Cypriot Syllabary", get32HextiINT("U+10800"), get32HextiINT("U+1083F")),
                    Plage("max.ttf", "Imperial Aramaic", get32HextiINT("U+10840"), get32HextiINT("U+1085F")),
                    Plage("max.ttf", "Phoenician", get32HextiINT("U+10900"), get32HextiINT("U+1091F")),
                    Plage("max.ttf", "Lydian", get32HextiINT("U+10920"), get32HextiINT("U+1093F")),
                    Plage("max.ttf", "Kharoshthi", get32HextiINT("U+10A00"), get32HextiINT("U+10A58")),
                    Plage("max.ttf", "Old South Arabian", get32HextiINT("U+10A60"), get32HextiINT("U+10A7F")),
                    Plage("max.ttf", "Avestan", get32HextiINT("U+10B00"), get32HextiINT("U+10B3F")),
                    Plage("max.ttf", "Inscriptional Parthian", get32HextiINT("U+10B40"), get32HextiINT("U+10B5F")),
                    Plage("max.ttf", "Inscriptional Pahlavi", get32HextiINT("U+10B60"), get32HextiINT("U+10B7F")),
                    Plage("max.ttf", "Old Turkic", get32HextiINT("U+10C00"), get32HextiINT("U+10C48")),
                    Plage("max.ttf", "Rumi Numeral Symbols", get32HextiINT("U+10E60"), get32HextiINT("U+10E7E")),
                    Plage("max.ttf", "Brahmi", get32HextiINT("U+11000"), get32HextiINT("U+1106F")),
                    Plage("max.ttf", "Kaithi", get32HextiINT("U+11080"), get32HextiINT("U+110C1")),
                    Plage("max.ttf", "Cuneiform", get32HextiINT("U+12000"), get32HextiINT("U+1236E")),
                    Plage("max.ttf", "Cuneiform Numbers and Punctuation", get32HextiINT("U+12400"), get32HextiINT("U+12473")),
                    Plage("max.ttf", "Egyptian Hieroglyphs", get32HextiINT("U+13000"), get32HextiINT("U+1342E")),
                    Plage("max.ttf", "Bamum Supplement", get32HextiINT("U+16800"), get32HextiINT("U+16A38")),
                    Plage("max.ttf", "Kana Supplement", get32HextiINT("U+1B000"), get32HextiINT("U+1B001")),
                    Plage("max.ttf", "Byzantine Musical Symbols", get32HextiINT("U+1D000"), get32HextiINT("U+1D0F5")),
                    Plage("max.ttf", "Musical Symbols", get32HextiINT("U+1D100"), get32HextiINT("U+1D1DD")),
                    Plage("max.ttf", "Ancient Greek Musical Notation", get32HextiINT("U+1D200"), get32HextiINT("U+1D245")),
                    Plage("max.ttf", "Tai Xuan Jing Symbols", get32HextiINT("U+1D300"), get32HextiINT("U+1D356")),
                    Plage("max.ttf", "Counting Rod Numerals", get32HextiINT("U+1D360"), get32HextiINT("U+1D371")),
                    Plage("max.ttf", "Mathematical Alphanumeric Symbols", get32HextiINT("U+1D400"), get32HextiINT("U+1D7FF")),
                    Plage("max.ttf", "Mahjong Tiles", get32HextiINT("U+1F000"), get32HextiINT("U+1F02B")),
                    Plage("max.ttf", "Domino Tiles", get32HextiINT("U+1F030"), get32HextiINT("U+1F093")),
                    Plage("max.ttf", "Playing Cards", get32HextiINT("U+1F0A0"), get32HextiINT("U+1F0DF")),
                    Plage("max.ttf", "Enclosed Alphanumeric Supplement", get32HextiINT("U+1F100"), get32HextiINT("U+1F1FF")),
                    Plage("max.ttf", "Enclosed Ideographic Supplement", get32HextiINT("U+1F200"), get32HextiINT("U+1F251")),
                    Plage("max.ttf", "Miscellaneous Symbols And Pictographs", get32HextiINT("U+1F300"), get32HextiINT("U+1F5FF")),
                    Plage("max.ttf", "Emoticons", get32HextiINT("U+1F601"), get32HextiINT("U+1F64F")),
                    Plage("max.ttf", "Transport And Map Symbols", get32HextiINT("U+1F680"), get32HextiINT("U+1F6C5")),
                    Plage("max.ttf", "Alchemical Symbols", get32HextiINT("U+1F700"), get32HextiINT("U+1F773")),
                    Plage("max.ttf", "CJK Unified Ideographs Extension B", get32HextiINT("U+20000"), get32HextiINT("U+2A6D6")),
                    Plage("max.ttf", "CJK Unified Ideographs Extension C", get32HextiINT("U+2A700"), get32HextiINT("U+2B734")),
                    Plage("max.ttf", "CJK Unified Ideographs Extension D", get32HextiINT("U+2B740"), get32HextiINT("U+2B81D")),
                    Plage("max.ttf", "CJK Compatibility Ideographs Supplement", get32HextiINT("U+2F800"), get32HextiINT("U+2FA1D")),
                    Plage("max.ttf", "Tags", get32HextiINT("U+E0001"), get32HextiINT("U+E007F")),
                    Plage("max.ttf", "Variation Selectors Supplement", get32HextiINT("U+E0100"), get32HextiINT("U+E01EF")),
                    Plage("max.ttf", "Supplementary Private Use Area-A", get32HextiINT("U+F0000"), get32HextiINT("U+FFFFD")),
                    Plage("max.ttf", "Supplementary Private Use Area-B", get32HextiINT("U+100000"), get32HextiINT("U+10FFFD"))*/
                    },
                    {
                    Plage("start1.ttf", "Basic Latin", get32HextiINT("U+0"), get32HextiINT("U+7F")),
                    Plage("start1.ttf", "Latin-1 Supplement", get32HextiINT("U+80"), get32HextiINT("U+FF")),
                    Plage("start1.ttf", "Latin Extended-A", get32HextiINT("U+100"), get32HextiINT("U+17F")),
                    Plage("start1.ttf", "Latin Extended-B", get32HextiINT("U+180"), get32HextiINT("U+24F")),
                    },
                    {
                    Plage("china1.ttf", "Enclosed CJK Letters and Months", get32HextiINT("U+3200"), get32HextiINT("U+32FE")),
                    Plage("china1.ttf", "CJK Compatibility", get32HextiINT("U+3300"), get32HextiINT("U+33FF")),
                    Plage("china1.ttf", "CJK Unified Ideographs Extension A", get32HextiINT("U+3400"), get32HextiINT("U+4DB5")),
                    Plage("china1.ttf", "CJK Unified Ideographs", get32HextiINT("U+4E00"), get32HextiINT("U+9FCB")),
                    Plage("china1.ttf", "CJK Compatibility Forms", get32HextiINT("U+FE30"), get32HextiINT("U+FE4F")),
                    Plage("china1.ttf", "CJK Compatibility Ideographs", get32HextiINT("U+F900"), get32HextiINT("U+FAD9")),
                    Plage("china1.ttf", "CJK Radicals Supplement", get32HextiINT("U+2E80"), get32HextiINT("U+2EF3"))
                    },
                    {
                    Plage("japan1.ttf", "Enclosed CJK Letters and Months", get32HextiINT("U+3200"), get32HextiINT("U+32FE"), 10000),
                    Plage("japan1.ttf", "CJK Compatibility", get32HextiINT("U+3300"), get32HextiINT("U+33FF"), 10000),
                    Plage("japan1.ttf", "CJK Unified Ideographs Extension A", get32HextiINT("U+3400"), get32HextiINT("U+4DB5"), 10000),
                    Plage("japan1.ttf", "CJK Unified Ideographs", get32HextiINT("U+4E00"), get32HextiINT("U+9FCB"), 10000),
                    Plage("japan1.ttf", "CJK Compatibility Forms", get32HextiINT("U+FE30"), get32HextiINT("U+FE4F"), 10000),
                    Plage("japan1.ttf", "CJK Compatibility Ideographs", get32HextiINT("U+F900"), get32HextiINT("U+FAD9"), 10000),
                    Plage("japan1.ttf", "CJK Radicals Supplement", get32HextiINT("U+2E80"), get32HextiINT("U+2EF3"), 10000)
                    },
                    {
                    Plage("korea.ttf", "Enclosed CJK Letters and Months", get32HextiINT("U+3200"), get32HextiINT("U+32FE"), 20000),
                    Plage("korea.ttf", "CJK Compatibility", get32HextiINT("U+3300"), get32HextiINT("U+33FF"), 20000),
                    Plage("korea.ttf", "CJK Unified Ideographs Extension A", get32HextiINT("U+3400"), get32HextiINT("U+4DB5"), 20000),
                    Plage("korea.ttf", "CJK Unified Ideographs", get32HextiINT("U+4E00"), get32HextiINT("U+9FCB"), 20000),
                    Plage("korea.ttf", "CJK Compatibility Forms", get32HextiINT("U+FE30"), get32HextiINT("U+FE4F"), 20000),
                    Plage("korea.ttf", "CJK Compatibility Ideographs", get32HextiINT("U+F900"), get32HextiINT("U+FAD9"), 20000),
                    Plage("korea.ttf", "CJK Radicals Supplement", get32HextiINT("U+2E80"), get32HextiINT("U+2EF3"), 20000)
                    }
            };

// Entry point of the program
int main() {
    
    GIB::build(fontFilenames);

    std::cout << "=== Program Finished ===\n";
    return 0;
}
