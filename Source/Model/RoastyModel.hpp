/* Roasty Model Header */
#pragma once

#include <string>

#define EVENT_ARRAY_SIZE 200
#define INGREDIENT_ARRAY_SIZE 200
#define DEFAULT_EVENT_VALUE 0

/* ============== Bean ================= */
class Bean 
{
public:
    Bean(std::string inputBeanName); // constructor
    std::string getName() const; 
private:
    std::string beanName; 
};

/* ============== Ingredients ================ */
class Ingredient
{
public:
    Ingredient& operator=(Ingredient const& other); // overload assignment operator
    Ingredient(Ingredient const& other); // copy-constructor
    Ingredient(const Bean& inputBean, int inputNewAmount); // constructor 
    ~Ingredient(); // destructor
    int getAmount() const; 
    Bean const& getBean() const;
private:
    int amount; 
    const Bean* bean; 
};

// ============== Event Value ================ */
class EventValue
{
public:
    EventValue(int inputEventValue); // constructor
    int getValue() const; 
private:
    int eventValue; 
};

/* ============== Event ================ */
class Event
{
public:
    Event& operator=(Event const& other); // overload assignment operator
    Event(Event const& other); // copy-constructor
    Event(std::string inputType, long inputTimestamp, EventValue* inputEventValue = nullptr); // constructor
    ~Event(); // destructor
    bool hasValue()const; 
    long getTimestamp() const; 
    EventValue* getValue() const; 
    std::string getType() const; 
    
private:
    EventValue* eventValue; 
    long timestamp; 
    std::string type; 

};

/* ============== Roasts ================ */
class Roast 
{
public:
    Roast& operator=(Roast const& other); // overload assignment operator
    Roast(Roast const& other); // copy-constructor
    Roast(long inputId, long inputBeginTimestamp); // constructor
    ~Roast(); // destructor
    long getId() const; 
    int getIngredientsCount() const; 
    int getEventCount() const; 
    long getTimestamp() const; 
    void addEvent(const Event& event); // i dont think the function needs to be const
    void addIngredient(const Ingredient& ingredient); 
    void removeEventByTimestamp(long eventTimestamp); 
    void removeIngredientByBeanName(std::string beanName); 
    Event const& getEvent(int number) const; // needs to return reference
    Ingredient const& getIngredient(int number) const; // needs to return reference
private:
    long roastId; 
    long beginTimestamp; 
    int eventCount = 0;
    int ingredientsCount = 0;
    const Event* eventArray[EVENT_ARRAY_SIZE]; 
    const Ingredient* ingredientArray[INGREDIENT_ARRAY_SIZE];
};
