#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <thread>
#include <chrono>
#include <algorithm>
#include <limits>

using namespace std;

struct UserProfile {
    string displayName;
    int userAge;
};

void storeUserProfile(const UserProfile& data) {
    ofstream file("profile_data.txt");
    if (file.is_open()) {
        file << data.displayName << endl;
        file << data.userAge << endl;
        file.close();
        cout << "Profile saved successfully!" << endl;
    } else {
        cerr << "Error: Unable to save profile." << endl;
    }

}

UserProfile fetchUserProfile() {
    UserProfile data;
    ifstream file("profile_data.txt");
    if (file.is_open()) {
        getline(file, data.displayName);
        file >> data.userAge;
        file.close();
        cout << "Profile loaded successfully!" << endl;
    } else {
        cout << "No existing profile found. Starting fresh." << endl;
    }
    return data;
}

// Emotion Logging
void captureEmotion(const string& feeling) {
    ofstream file("emotion_log.txt", ios::app);
    if (file.is_open()) {
        time_t now = time(0);
        string timestamp = ctime(&now);
        timestamp.pop_back();
        file << feeling << " | " << timestamp << endl;
        file.close();
    }
}

void recentEmotions() {
    ifstream file("emotion_log.txt");
    string entry;
    cout << "\n📝 Previous Emotions:\n";
    int count = 0;
    vector<string> history;
    while (getline(file, entry) && count < 5) {
        history.push_back(entry);
        count++;
    }
    reverse(history.begin(), history.end());
    for (const auto& line : history) {
        cout << line << endl;
    }
    file.close();
}

// Helpers
void recommendActivity(const string& mood) {
    map<string, vector<string>> activities = {
        {"happy", {"Keep smiling 😄", "Enjoy some music 🎵", "Call a friend ☎️"}},
        {"sad", {"Take a walk 🌿", "Write in a diary 📓", "Meditate 🧘"}},
        {"stressed", {"Breathe deeply 🌬️", "Try yoga 🧎", "Take a short nap 😴"}},
        {"angry", {"Do a workout 🏋️", "Listen to calm tunes 🎶", "Write down your feelings ✍️"}},
        {"tired", {"Take a power nap", "Drink some water", "Stretch your body"}},
        {"anxious", {"Practice deep breathing", "Try grounding techniques", "Make a to-do list"}}
    };

    string moodLower = mood;
    transform(moodLower.begin(), moodLower.end(), moodLower.begin(), ::tolower);

    cout << "\n🌟 Suggestions for '" << mood << "':\n";
    if (activities.find(moodLower) != activities.end()) {
        for (auto& task : activities[moodLower]) {
            cout << "- " << task << endl;
        }
    } else {
        cout << "No activities found. Try relaxing! 😊" << endl;
    }
}

map<string, int> moodStats() {
    ifstream file("emotion_log.txt");
    string line;
    map<string, int> stats;

    if (!file.is_open()) return stats;

    while (getline(file, line)) {
        string mood = line.substr(0, line.find(" | "));
        stats[mood]++;
    }
    return stats;
}

string randomInspiration() {
    vector<string> sayings = {
        "Stay strong, better days are ahead 💪",
        "You are capable of amazing things 🌟",
        "Every day is a fresh start 🌅",
        "Focus on progress, not perfection 🚀",
        "Believe in yourself ✨"
    };
    return sayings[rand() % sayings.size()];
}

void relaxationBreathing() {
    cout << "\n🌬️ Guided Breathing: Inhale for 4s, hold for 4s, exhale for 4s.\n";
    for (int i = 0; i < 3; i++) {
        cout << "Inhale...\n"; this_thread::sleep_for(chrono::seconds(4));
        cout << "Hold...\n"; this_thread::sleep_for(chrono::seconds(4));
        cout << "Exhale...\n"; this_thread::sleep_for(chrono::seconds(4));
    }
    cout << "✨ Session complete. You should feel calmer!\n";
}

void gratitudeNote() {
    ofstream file("gratitude_notes.txt", ios::app);
    string note;
    cout << "🙏 Write something you're grateful for today: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, note);
    file << note << endl;
    cout << "🌸 Noted! Gratitude helps positivity.\n";
}

void readGratitudeNotes() {
    ifstream file("gratitude_notes.txt");
    string line;
    cout << "\n🌼 Your Gratitude Notes:\n";
    while (getline(file, line)) {
        cout << "- " << line << endl;
    }
}

// Menu System
int main() {
    srand(time(0));
    UserProfile user = fetchUserProfile();

    if (user.displayName.empty()) {
        cout << "Enter your name: ";
        getline(cin, user.displayName);
        cout << "Enter your age: ";
        cin >> user.userAge;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        storeUserProfile(user);
    }

    int option;
    do {
        cout << "\n===== Mental Wellness Hub =====\n";
        cout << "1. Record Emotion\n";
        cout << "2. View Emotion History\n";
        cout << "3. Get Activity Suggestion\n";
        cout << "4. Emotion Frequency Stats\n";
        cout << "5. Daily Motivation\n";
        cout << "6. Breathing Guide\n";
        cout << "7. Write Gratitude Note\n";
        cout << "8. Show Gratitude Notes\n";
        cout << "9. Exit\n";
        cout << "Select an option: ";

        if (!(cin >> option)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Invalid choice. Try again.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (option) {
            case 1: {
                string mood;
                cout << "How are you feeling? (happy, sad, anxious, angry, tired, stressed): ";
                getline(cin, mood);
                captureEmotion(mood);
                recommendActivity(mood);
                break;
            }
            case 2: recentEmotions(); break;
            case 3: {
                string mood;
                cout << "Enter mood to get suggestions: ";
                getline(cin, mood);
                recommendActivity(mood);
                break;
            }
            case 4: {
                auto stats = moodStats();
                cout << "\n📊 Mood Frequency:\n";
                for (auto& p : stats) {
                    cout << p.first << ": " << p.second << endl;
                }
                break;
            }
            case 5: cout << "Motivational quote: " << randomInspiration() << endl; break;
            case 6: relaxationBreathing(); break;
            case 7: gratitudeNote(); break;
            case 8: readGratitudeNotes(); break;
            case 9: cout << "👋 Goodbye! Stay positive.\n"; break;
            default: cout << "❌ Invalid option.\n";
        }
    } while (option != 9);

    return 0;
}