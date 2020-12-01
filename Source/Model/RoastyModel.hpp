/* Roasty Model Header */
#pragma once

#include <string>


// Initial array size of 6 is assumed since there are 
// 6 events that could take place in any roasting proccess 
#define INITIAL_ARRAY_SIZE 6

/* ============== Bean ================= */
class Bean 
{
public:
    Bean(std::string inputBeanName); // constructor
    Bean(Bean const& other); // copy-constructor
    Bean& operator=(Bean const& other); // overload assignment operator
    ~Bean(){} // destructor
    std::string getName() const; 
private:
    std::string beanName; 
};

/* ============== Ingredients ================ */

class Ingredient 
{
public:
    Ingredient(Bean& inputBean, int inputNewAmount); // user-dfined constructor 
    Ingredient(Ingredient const& other); // copy-constructor
    Ingredient& operator=(Ingredient const& other); // overload assignment operator
    ~Ingredient(); // destructor
    int getAmount() const; 
    Bean const& getBean() const;
private:
    int amount; 
    /* Ingredient has the ownership of Bean objects */
    Bean& bean; 
};

// ============== Event Value ================ */

class EventValue
{
public:
    EventValue(int inputEventValue); // user-defined constructor
    EventValue(EventValue const& other); // copy-constructor
    EventValue& operator=(EventValue const& other); // overload assignment operator
    int getValue() const; 
private:
    int eventValue; 
};

/* ============== Event ================ */

class Event 
{
public:
    Event(std::string inputType, long inputTimestamp, EventValue* inputEventValue = nullptr); // user-defined constructor
    Event(Event const& other); // copy-constructor
    Event& operator=(Event const& other); // overload assignment operator
    ~Event(); // destructor
    bool hasValue()const; 
    long getTimestamp() const; 
    EventValue* getValue() const; 
    std::string getType() const; 
    
private:
    long timestamp; 
    std::string type; 
    /* Event has the ownership of EventValue objects */
    EventValue* eventValue; 

};

/* ============== Roasts ================ */

class Roast 
{
public:
    Roast(long inputId, long inputBeginTimestamp); // user-defined constructor
    Roast(Roast const& other); // copy-constructor
    Roast& operator=(Roast const& other); // overload assignment operator
    ~Roast(); // destructor
    long getId() const; 
    int getIngredientsCount() const;
    int getEventCount() const; 
    long getTimestamp() const;
    void addEvent(const Event& event); 
    void addIngredient(const Ingredient& ingredient); 
    void removeEventByTimestamp(long eventTimestamp); 
    void removeIngredientByBeanName(std::string beanName); 
    Event const& getEvent(int number) const; 
    Ingredient const& getIngredient(int number) const; 
private:
    long roastId; 
    long beginTimestamp; 
    int eventCount;
    int ingredientsCount;
    int eventArrayCapacity = INITIAL_ARRAY_SIZE;
    int ingredientArrayCapacity = INITIAL_ARRAY_SIZE;
    /* Roast has the ownership ot these objects- delete them */
    const Event* * eventArray = new const Event*[eventArrayCapacity]; 
    const Ingredient* * ingredientArray = new const Ingredient*[ingredientArrayCapacity];
    /* 
    DEAR MARKER
    Ideally, I would implment the above resizable arrays by writing my own templated class
    (or just using std::vector) but since we are not allowed to use templates at all 
    I incooperated the "resizability" into addIngredient() and addEvent().
    */
};
