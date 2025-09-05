#include <string>
#include <vector>
#include <set>

struct NewsworthyItem {
    std::string name;
    std::string subject;
    float importanceScore;
};

struct Subject {
    int ranking;
    std::string name;
};

struct PlayerProperties {
    std::vector<NewsworthyItem> memoryBank;
    std::vector<Subject> subjects;
    int subjectCount;
    int conversationLength;
    int itemCount;
};


class Player {

private:
    std::vector<NewsworthyItem> memoryBank;
    std::vector<Subject> subjects;
    int subjectCount;
    int conversationLength;
    int itemCount;
    
    std::vector<NewsworthyItem> contributionHistory;
    int individualScore;

    static std::vector<NewsworthyItem> conversationHistory;
    static int netScore;

public:
    Player(PlayerProperties pp) {
        this->conversationLength = pp.conversationLength;
        this->itemCount = pp.itemCount;
        this->subjectCount = pp.subjectCount;
        this->memoryBank = pp.memoryBank;
        this->subjects = pp.subjects;
    }

    /**
     * Note this can be used to limit the probability to people whose 
     * conversation items would most benefit the scores.
     * 
     * Calculate the score increase if this person contributes, if that is 
     * more than some threshold value then contribute to the conversation.
     */
    bool isWilllingToContribute();
        
};
