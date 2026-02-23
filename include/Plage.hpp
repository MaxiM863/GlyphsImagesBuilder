#include <string>

class Plage{

    public:
        Plage(std::string fontFilename, std::string unicodeName, int startPos, int endPos, int jumpForCJK = 0){
            
            this->startPos = startPos;
            this->endPos = endPos;
            this->fontFilename = fontFilename;
            this->UnicodeName = unicodeName;
            this->jumpForCJK = jumpForCJK;

        };

        int jumpForCJK;
        int startPos;
        int endPos;
        std::string fontFilename;
        std::string UnicodeName;
};