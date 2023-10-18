#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;
bool KMP(vector<string>& nums, vector<string>& group);

int main(int argc, const char * argv[]) {
    
    bool output = true;
    bool check = false;
    int num_cases;
    cout << "Enter the number of the Test Case you want to run: ";
    cin >> num_cases;
    
    ifstream file("TestCase.txt");
    string line;
    
    vector<vector<string>> groups;
    while (getline(file, line))
    {
        auto starting = line.find('{');
        auto ending = line.find('}', starting + 1);
        
        for (;starting != -1 && ending != -1;)
        {
            vector<string> group;
            auto sAnde_bracing = ending - starting;
            string group_str = line.substr(starting + 1, sAnde_bracing - 1);
            
            auto content_starting = group_str.find('\'');
            auto content_ending = group_str.find('\'', content_starting + 1);
            
            for (;content_starting != -1 && content_ending != -1;)
            {
                auto content_check = content_ending - content_starting;
                string content;
                content = group_str.substr(content_starting + 1, content_check - 1);
                
                group.push_back(content);
                
                content_starting = group_str.find('\'', content_ending + 1);
                content_ending = group_str.find('\'', content_starting + 1);
            }
            groups.push_back(group);
            starting = line.find('{', ending + 1);
            ending = line.find('}', starting + 1);
        }
    }
    file.close();
    
    cout << "Groups = ";
    for (int j = 0; j < groups.size(); j++) {
        for (int k = 0; k < groups[j].size(); k++) {
            cout << groups[j][k] << " ";
        }
        cout << endl;
    }
    
    
    file.open("p1_input.txt");
    vector<vector<string>> test;
    string line1;
    
    string test_case;
    switch (num_cases)
    {
        case 1:
            test_case = "Test case 1";
            break;
        case 2:
            test_case = "Test case 2";
            break;
        case 3:
            test_case = "Test case 3";
            break;
        case 4:
            test_case = "Test case 4";
            break;
        case 5:
            test_case = "Test case 5";
            break;
            
        default:
            cout << "Invalid Option Selected" << endl;
            break;
    }
    
    while (getline(file, line1))
    {
        
        if (line1.find(test_case) != -1)
        {
            
            getline(file, line1);
            
            auto starting_ = line1.find('[');
            auto ending_ = line1.find(']', starting_ + 1);
            
            while (starting_ != -1 && ending_ != -1)
            {
                vector<string> group;
                auto sub = ending_ - starting_;
                string numsString = line1.substr(starting_ + 1, sub - 1);
                
                auto content_starting = numsString.find('\'');
                auto content_ending = numsString.find('\'', content_starting + 1);
                
                while (content_starting != -1 && content_ending != -1)
                {
                    
                    auto content_check = content_ending - content_starting;
                    string content_ = numsString.substr(content_starting + 1, content_check - 1);
                    group.push_back(content_);
                    
                    content_starting = numsString.find('\'', content_ending + 1);
                    content_ending = numsString.find('\'', content_starting + 1);
                }
                test.push_back(group);
                
                starting_ = line1.find('[', ending_ + 1);
                ending_ = line1.find(']', starting_ + 1);
            }
        }
    }
    
    file.close();
    
    cout << "Nums = ";
    for (int i = 0; i < test.size(); i++) {
        for (int j = 0; j < test[i].size(); j++) {
            cout << test[i][j] << " ";
        }
        cout << endl;
    }
    
    for (vector<string>& group : groups) {
        for (vector<string>& nums : test) {
            if (KMP(nums, group) == false) {
                output = false;
                check = true;
                break;
            }
            if (check == false)
                break;
        }
    }
    
    if (output == false) {
        cout << "False\n";
    } else {
        cout << "True\n";
    }
}

bool KMP(vector<string>& nums, vector<string>& group) {
    
    unordered_map<string, bool> grVec;
    int x = 0;
    int y = 1;
    bool comp;
    
    vector<string> used;
    for (const auto& elem : group) {
        grVec[elem] = 1;
    }

    while (x < nums.size())
    {
        if (grVec.count(nums[x]) == true) {
            comp = true;
            for (y = 1; y < group.size(); ++y)
            {
                int sum = x+y;
                if (!grVec.count(nums[sum]) || sum >= nums.size())
                {
                    comp = false;
                    break;
                }
            }
            if (comp == true) {
                int k = 0;
                while (k < group.size()) {
                    int count = x+k;
                    used.push_back(nums[count]);
                    ++k;
                }

                vector<string> nums_copy(nums.begin(), nums.end());
                
                auto Iterate_Begining = (nums_copy.begin() + x + group.size());
                nums_copy.erase(nums_copy.begin() + x, Iterate_Begining);
                nums = nums_copy;
                x = 0;
                continue;
            }
        }
        ++x;
    }
    return (used.empty() == false);
}
