// === Region: Project Overview ===
//
//  COMP2011 Fall 2024
//  PA3: Social-Networking-Platform-Prototype
//
//  Your name: KUSNADI, Vicko Nicholas
//  Your ITSC email: vnkusnadi@connect.ust.hk
//
// =====================================

// === Region: Necessary header files ===
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
using namespace std;

const int MAX_CHAR_NUM =
100; // at most 100 characters (including the NULL character)

// A linked list of Users
struct User {
    unsigned int uid;     // id is an unique identifier of the User (e.g., 39)
    char name[MAX_CHAR_NUM]; // name of the User
    User* next; // The pointer pointing to the next User
};

// A linked list in which every node points to a user
struct Like_Node {
    User* User_ptr;
    Like_Node* next;
};

// Struct representing a Post (which is anonymous).
struct Post {
    unsigned int pid;           // id is an unique identifier of the post (e.g., 39)
    char content[MAX_CHAR_NUM];        // the content of the post
    int num_of_likes; // number of sharing of this post
    Like_Node* likes;            // Linked list of users that like this post
};

User* create_user(const unsigned int uid, const char name[MAX_CHAR_NUM]) {
    User* new_user = new User;
    new_user->uid = uid;
    strcpy(new_user->name, name);
    new_user->next = nullptr;
    return new_user;
}

Post* create_post(const unsigned int pid,
    const char content[MAX_CHAR_NUM]) {
    Post* new_post = new Post;
    new_post->pid = pid;
    strcpy(new_post->content, content);
    new_post->num_of_likes = 0;
    new_post->likes = nullptr;
    return new_post;
}

// Given the number of posts, dynamicially creates and initializes the posts
// list array
Post** dynamic_init_posts_array(const unsigned int posts_array_size) {
    Post** ret = nullptr;
    ret = new Post * [posts_array_size];
    for (int i = 0; i < posts_array_size; i++)
        ret[i] = nullptr;
    return ret;
}

// Helper function: search user and return prev, current
// return true if found an existing entry
// return false if an existing entry is not found
bool search_user(User* head, const unsigned int uid, User*& prev,
    User*& current) {
    prev = nullptr;
    for (current = head; current != nullptr; current = current->next) {
        if (current->uid == uid) {
            // found an existing entry
            return true;
        }
        else if (current->uid > uid) {
            // cannot find an existing entry
            return false;
        }
        prev = current;
    }
    return false;
}

// Helper function: search like and return prev, current
// return true if found an existing entry
// return false if an existing entry is not found
bool search_like(Like_Node* head, const unsigned int uid, Like_Node*& prev,
    Like_Node*& current) {
    prev = nullptr;
    for (current = head; current != nullptr; current = current->next) {
        if (current->User_ptr->uid == uid) {
            // found an existing entry
            return true;
        }
        prev = current;
    }
    return false;
}


bool search_post(Post**& posts_array, const unsigned int pid,
    const unsigned int posts_array_size, int& i) {
    Post* post;
    if (posts_array != nullptr) {
        for (i = 0; i < posts_array_size; i++) {
            post = posts_array[i];
            if (post == nullptr) {
                break;
            }

            if (post->pid == pid) {
                // found an existing entry
                return true;
            }
        }
    }
    return false;
}


void print_user(const User* user) {
    cout << "User Id: " << user->uid << ", name: " << user->name << "\n";
}



void print_post(const Post* post) {
    cout << "Post Id: " << post->pid << ", " << post->num_of_likes << " likes, content: " << post->content << "\n";
}




// TASK 1: Adds a user to the users's linked list.
// This function takes as input:
//      1) the users list
//      2) the user id
//      3) its name.
// And works as follows:
//      1) If there is a user with the same user id return false
//      2) Otherwise,
//          a) Add the user maintaining an increasing order
//              of user ids in the list (see examples bellow)
//          b) return true

bool add_user(User*& user_head, const unsigned int uid,
    const char name[MAX_CHAR_NUM]) {
    // TODO: Write code to implement add_user
    User* prev = nullptr;
    User* current = nullptr;

    // User with uid already exists
    if (search_user(user_head, uid, prev, current)) {
        return false;
    }
    else {
        User* new_user = create_user(uid, name);
        if (prev == nullptr) {
            new_user->next = user_head;
            user_head = new_user;
        }
        else {
            new_user->next = current;
            prev->next = new_user;
        }
        return true;
    }
}



// TASK 2: Display all users:
// This function takes as input:
//      1) the users list
// And works as follows:
//      1) If: there is no user, display the No-user-message
//      2) Else: Traverse the list, and invoke the GIVEN function
//              print_user_data(User *user) to print the data of each user
void display_users(User* user_head) {
    // TODO: Write code to implement
    // Print this first and return imidiately if there are no users
    // when no users exist
    if (user_head == nullptr) {
        cout << "No users in the system yet" << "\n";
        return;
    }
    cout << "=== Users List ([uid, name]) ===" << endl;
    User* current = user_head;
    while (current != nullptr) {
        print_user(current);
        current = current->next;
    }
}



// TASK 3: Adds a new post in the posts array of pointers.
// This function takes as input:
//      1) the posts array
//      2) the post id
//      3) the content of the post
//      4) the posts array size
// And works as follows:
//      1) If the post exists (there is a post with the post_id), return false.
//      2) Otherwise:
//          a) if there is empty space:
//              i) Insert the post (in the next empty cell)
//             ii) return true.
//          b) Else:
//              i) Double the array size (e.g., if the array has size 16, then increase it to size 32) and then add the post
//            ii) return true.
bool add_post(Post**& posts_array, const unsigned int pid,
    const char content[MAX_CHAR_NUM], unsigned int& posts_array_size) {
    // TODO: Write code to implement add_post
    int index = 0;
    // post exist
    if (search_post(posts_array, pid, posts_array_size, index)) {
        return false;
    }
    if (index < static_cast<int>(posts_array_size)) {
        posts_array[index] = create_post(pid, content);
        return true;
    }
    else {
        unsigned int new_size = posts_array_size * 2;
        Post** new_posts_array = new Post * [new_size];

        for (unsigned int i = 0; i < new_size; i++) {
            new_posts_array[i] = nullptr;
        }
        for (unsigned int i = 0; i < posts_array_size; i++) {
            new_posts_array[i] = posts_array[i];
        }


        delete[] posts_array;
        posts_array = new_posts_array;
        posts_array_size = new_size;

        posts_array[index] = create_post(pid, content);
        return true;
    }
}



// TASK 4: Display all posts:
// This function takes as input:
//      1) the posts array
//      2) the posts array size
// And works as follows:
//      1) Traverse the array, and invoke the GIVEN function
//              print_post_data(Post *post) to print the data of each post
// ** DISCLAIMER**: You MUST not modify any GIVEN function or the contents of given cout's.
void display_posts(Post** posts_array, const unsigned int posts_array_size) {
    // TODO: Write code to implement display_posts
    for (unsigned int i = 0; i < posts_array_size; i++) {
        if (posts_array[i] != nullptr) {
            print_post(posts_array[i]);
        }
    }
}



// TASK 5: A user likes a specific post:
// This function takes as input:
//      1) the users list
//      2) the array of posts
//      3) the id of the user that likes the post,
//      4) the id of the like post
//      5) the posts array size
// And works as follow:
//      1) If the user does not exist return false
//      2) If the post does not exist return false
//      3) If the user already likes the post, return false
//      4) Otherwise, add the like by:
//          a) Adding a new node in the Likes_List that points
//                to the user who likes the post
//          b) Incrementing the number of likes
//          c) return true
bool add_like(User*& user_head,
    Post**& posts_array, unsigned int uid, unsigned int pid,
    const unsigned int posts_array_size) {
    // TODO: Write code to implement add_like
    // Check if user exists
    User* prev_user = nullptr;
    User* current_user = nullptr;

    // check if user do not exist
    if (!search_user(user_head, uid, prev_user, current_user)) {
        return false;
    }
    // check if post exists
    int index = 0;
    if (!search_post(posts_array, pid, posts_array_size, index)) {
        // Post does not exist
        return false;
    }
    // check if user already likes the post
    Like_Node* prev_like = nullptr;
    Like_Node* current_like = nullptr;
    if (search_like(posts_array[index]->likes, uid, prev_like, current_like)) {
        return false;
    }

    Like_Node* new_like = new Like_Node;
    new_like->User_ptr = current_user;
    new_like->next = posts_array[index]->likes;
    posts_array[index]->likes = new_like;
    posts_array[index]->num_of_likes++;
    return true;
}



// TASK 6: Delete a like made by a user on a specific post:
// This function takes as input:
//      1) the users list
//      2) the posts array
//      3) the id of the user who wants to delete its like,
//      4) the id of the post
//      5) the size of the posts array
// And works as follow:
//      1) If the post is not liked by the specific user return false
//      2) If the post does not exist return false
//      3) Otherwise,
//          a) Remove the correspodning node from the Likes_List
//          b) decrease the num_of_likes of that post
//          c) return true

bool delete_like(User* user_head, Post**& posts_array, const unsigned int uid, const unsigned int pid, int posts_array_size) {
    // TODO: Write code to implement delete_like
    // cout << "Failed to find the user" << "\n"; // print this if the user does not exist
    // cout << "Failed to find the post" << "\n"; // print this if the post does not exist
    // *** First search for the users and then for the posts ***
    User* prev_user = nullptr;
    User* current_user = nullptr;
    if (!search_user(user_head, uid, prev_user, current_user)) {
        cout << "Failed to find the user" << "\n"; // print this if the user does not exist
        return false;
    }
    int index = 0;
    if (!search_post(posts_array, pid, posts_array_size, index)) {
        cout << "Failed to find the post" << "\n"; // print this if the post does not exist
        return false;
    }
    // search for the like
    Like_Node* prev_like = nullptr;
    Like_Node* current_like = nullptr;
    if (!search_like(posts_array[index]->likes, uid, prev_like, current_like)) {
        return false;
    }
    // remove the like node
    if (prev_like == nullptr) {
        posts_array[index]->likes = current_like->next;
    }
    else {
        prev_like->next = current_like->next;
    }
    delete current_like;
    posts_array[index]->num_of_likes--;
    return true;
}



// TASK 7: Delete a user:
// This function takes as input:
//      1) the users list
//      2) the posts array
//      3) the id of the user to be deleted,
// And works as follow:
//      1) If the user does not exist return false
//      2) Otherwise,
//          a) First remove all likes made by this user
//          b) Delete the user from the users list
//          c) return true

bool delete_user(User*& user_head, Post**& posts_array, const unsigned int uid, const unsigned int posts_array_size) {
    // TODO: Write code to implement delete_user
    // cout << "Failed to find the user" << "\n";// print this if the user does not exist.

    // search for the user
    User* prev_user = nullptr;
    User* current_user = nullptr;
    if (!search_user(user_head, uid, prev_user, current_user)) {
        cout << "Failed to find the user" << "\n";// print this if the user does not exist.
        return false;
    }
    // remove all likes made by this user
    for (unsigned int i = 0; i < posts_array_size; i++) {
        Post* post = posts_array[i];
        if (post != nullptr) {
            Like_Node* prev_like = nullptr;
            Like_Node* current_like = post->likes;
            while (current_like != nullptr) {
                if (current_like->User_ptr->uid == uid) {
                    Like_Node* to_delete = current_like;
                    if (prev_like == nullptr) {
                        post->likes = current_like->next;
                    }
                    else {
                        prev_like->next = current_like->next;
                    }
                    current_like = current_like->next;
                    delete to_delete;
                    post->num_of_likes--;
                    continue;
                }
                else {
                    prev_like = current_like;
                    current_like = current_like->next;
                }
            }
        }
    }
    // delete the user from the users list
    if (prev_user == nullptr) {
        user_head = current_user->next;
    }
    else {
        prev_user->next = current_user->next;
    }
    delete current_user;
    return true;

}


// TASK 8: Finds the posts with the largest number of likes:
// This function takes as input:
//      1) the posts array
//      2) the posts array size
// And works as follow:
//      1) If there is not post yet, return false
//      2) Otherwise,
//          a) Find the post with the largest number of likes
//          b) If two posts have the same number of likes, pick the first one (e.g., the oldest one).
//          c) After finding this post, use the print_post_data to print it.
//          d) return true
bool find_popular_post(Post**& posts_array, const int posts_array_size) {
    // TODO: Write code to implement find_popular_post
    // *** Use the print_post_data to print the most popular post ***
    Post* most_popular_post = nullptr;
    bool found = false;
    int max_likes = -1;
    for (int i = 0; i < posts_array_size; i++) {
        if (posts_array[i] != nullptr) {
            Post* post = posts_array[i];
            if (!found || post->num_of_likes > max_likes) {
                most_popular_post = post;
                max_likes = post->num_of_likes;
                found = true;
            }
        }
    }
    if (!found) {
        return false;
    }
    else {
        print_post(most_popular_post);
        return true;
    }
}



// TASK 9: Clean up all data before entering your system
void clean_up(User*& user_head, Post**& posts_array, unsigned int& posts_array_size) {
    // TODO:
    // delete all posts, likes and users, be carefully for the memory leak
    // delete all users
    User* current_user = user_head;
    while (current_user != nullptr) {
        User* to_delete = current_user;
        current_user = current_user->next;
        delete to_delete;
    }
    user_head = nullptr;

    // delete all posts and their likes
    for (unsigned int i = 0; i < posts_array_size; i++) {
        Post* post = posts_array[i];
        if (post != nullptr) {

            Like_Node* current_like = post->likes;
            while (current_like != nullptr) {
                Like_Node* like_to_delete = current_like;
                current_like = current_like->next;
                delete like_to_delete;
            }
            post->likes = nullptr;

            delete post;
            posts_array[i] = nullptr;
        }
    }
    // delete the posts array
    delete[] posts_array;
    posts_array = nullptr;
    posts_array_size = 0;
}






// === Region: The main function ===
// The main function implementation is given
// DO NOT make any changes to the main function
// ============================
int main() {
    enum MeunOption {
        OPTION_INSERT_USER = 0,
        OPTION_DISPLAY_USER_LIST,
        OPTION_INSERT_POST,
        OPTION_DISPLAY_POSTS,
        OPTION_INSERT_LIKE,
        OPTION_DELETE_LIKE,
        OPTION_DELETE_USER,
        OPTION_DISPLAY_POPULAR_POST,
        OPTION_EXIT_SYSTEM,
        MAX_MENU_OPTIONS
    };
    const int MAX_MENU_OPTIONS_LENGTH = 80;
    char menu_options[MAX_MENU_OPTIONS][MAX_MENU_OPTIONS_LENGTH] = {
        "Insert a new user",
        "Display Users",
        "Insert a new post",
        "Display Posts",
        "Like a post",
        "Unlike a post",
        "Delete a user",
        "Display most popular post ",
        "Exit the system" };

    User* user_head = nullptr;
    Post** posts_array = nullptr;
    unsigned int posts_array_size = 0;
    int i, option;
    int uid, pid;
    char name[MAX_CHAR_NUM] = "";
    char content[MAX_CHAR_NUM] = "";
    bool ret = false;

    posts_array_size = 2;
    posts_array = dynamic_init_posts_array(posts_array_size);

    cout << "=== Simplified social network ===" << endl;
    while (true) {
        cout << "=== Menu ===" << endl;
        for (i = 0; i < MAX_MENU_OPTIONS; i++)
            cout << i + 1 << ": " << menu_options[i]
            << endl; // shift by +1 when display

        cout << "Enter your option: " << endl;
        cin >> option;
        option = option - 1; // shift by -1 after entering the option

        // The invalid menu option handling
        if (option < 0 || option >= MAX_MENU_OPTIONS) {
            cout << "Invalid option" << endl;
            continue;
        }

        // Exit operations handling
        if (option == OPTION_EXIT_SYSTEM) {
            cout << "Cleaning memory" << endl;
            clean_up(user_head, posts_array, posts_array_size);
            break; // break the while loop
        }
        switch (option) {
        case OPTION_DISPLAY_USER_LIST:
            display_users(user_head);
            break;
        case OPTION_DISPLAY_POSTS:
            display_posts(posts_array, posts_array_size);
            break;
        case OPTION_INSERT_USER:
            uid = 0;
            cout << "Enter the user id: " << endl;
            cin >> uid;
            if (uid <= 0) {
                cout << "Enter a valid user id > 0" << endl;
                break;
            }
            cout << "Enter a name: " << endl;
            cin >> name;

            ret = add_user(user_head, uid, name);
            if (ret == false) {
                cout << "Failed to insert user " << uid << endl;
            }
            else {
                cout << uid << " inserted to the network" << endl;
            }
            break;
        case OPTION_INSERT_POST:
            pid = 0;
            cout << "Enter the post id: " << endl;
            cin >> pid;
            if (pid <= 0) {
                cout << "Enter a valid post id > 0" << endl;
                break;
            }
            cout << "Add content: " << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.getline(content, MAX_CHAR_NUM);

            ret = add_post(posts_array, pid, content, posts_array_size);
            if (ret == false) {
                cout << "Failed to insert post " << pid << endl;
            }
            else {
                cout << pid << " successfully posted" << endl;
            }
            break;
        case OPTION_INSERT_LIKE:
            uid = 0;
            cout << "Enter the user id: " << endl;
            cin >> uid;
            if (uid <= 0) {
                cout << "Enter a valid user id > 0" << endl;
                break;
            }
            pid = 0;
            cout << "Enter the post id: " << endl;
            cin >> pid;
            if (pid <= 0) {
                cout << "Enter a valid post id > 0" << endl;
                break;
            }

            ret = add_like(user_head, posts_array, uid, pid, posts_array_size);
            if (ret == false) {
                cout << "Failed to like, uid: " << uid
                    << ", pid: " << pid << endl;
            }
            else {
                cout << "A like is successfully inserted" << endl;
            }
            break;
        case OPTION_DELETE_LIKE:
            uid = 0;
            cout << "Enter the user id: " << endl;
            cin >> uid;
            if (uid <= 0) {
                cout << "Enter a valid user id > 0" << endl;
                break;
            }
            pid = 0;
            cout << "Enter the post id: " << endl;
            cin >> pid;
            if (pid <= 0) {
                cout << "Enter a valid post id > 0" << endl;
                break;
            }

            ret = delete_like(user_head, posts_array, uid, pid,
                posts_array_size);
            if (ret == false) {
                cout << "Failed to delete like, uid: " << uid
                    << ", pid: " << pid << endl;
            }
            else {
                cout << "The like is successfully deleted" << endl;
            }
            break;
        case OPTION_DELETE_USER:
            uid = 0;
            cout << "Enter the user id: " << endl;
            cin >> uid;
            if (uid <= 0) {
                cout << "Enter a valid post id > 0" << endl;
                break;
            }

            ret = delete_user(user_head, posts_array, uid, posts_array_size);
            if (ret == false) {
                cout << "Failed to delete user, user id: " << uid << endl;
            }
            else {
                cout << "user successfully deleted" << endl;
            }
            break;
        case OPTION_DISPLAY_POPULAR_POST:

            ret = find_popular_post(posts_array, posts_array_size);
            if (ret == false) {
                cout << "No posts in the network yet" << endl;
            }
            break;
        default:
            break;
        } // end of switch (option)
    }

    return 0;
}
