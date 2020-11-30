/* Roasty Model Header */
#pragma once

#include <string>

#define INITIAL_ARRAY_SIZE 2

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

class Ingredient // Ingredient owns Bean class objects
{
public:
    Ingredient(const Bean& inputBean, int inputNewAmount); // user-dfined constructor 
    Ingredient(Ingredient const& other); // copy-constructor
    Ingredient& operator=(Ingredient const& other); // overload assignment operator
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

class Event // Event owns EventValue class objects
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
    EventValue* eventValue; 
    long timestamp; 
    std::string type; 

};

/* ============== Roasts ================ */

class Roast // Roast owns Ingredient and Event class objects
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
    const Event* * eventArray = new const Event*[eventArrayCapacity]; 
    const Ingredient* * ingredientArray = new const Ingredient*[ingredientArrayCapacity];
};
