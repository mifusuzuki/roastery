/* Roasty Model Header */

#pragma once

#include <string>

/* Initial array size of 6 is assumed since there are six
events that could take place in any roasting proccess */
#define INITIAL_ARRAY_SIZE 6

/***********************************************
                    Bean  
************************************************/

class Bean 
{
public:
    /* Constructor */
    Bean(std::string inputBeanName); 
    /* Copy-constructor */
    Bean(Bean const& other); 
    /* Overload assignment operator */
    Bean& operator=(Bean const& other); 
    /* Destructor */
    ~Bean(){} 
    /* Getter function for beanName */
    std::string getName() const; 
private:
    std::string beanName; 
};

/***********************************************
                 Ingredient 
 * Ingredient has the ownership of bean objects 
************************************************/

class Ingredient 
{
public:
    /* Constructor */   
    Ingredient(Bean& inputBean, int inputNewAmount); 
    /* Copy-constructor */
    Ingredient(Ingredient const& other); 
    /* Overload assignment operator */
    Ingredient& operator=(Ingredient const& other); 
    /* Destructor */
    ~Ingredient();
    /* Getter function for amount */
    int getAmount() const; 
    /* Getter function for bean object */
    Bean const& getBean() const;
private:
    int amount; 
    Bean& bean; // Owned by Ingredient object
     
};

/*******************************************
                 EventValue  
*******************************************/

class EventValue
{
public:
    /* Constructor */
    EventValue(int inputEventValue); 
    /* Copy-constructor */
    EventValue(EventValue const& other); 
    /* Overload assignment operator */
    EventValue& operator=(EventValue const& other);
    /* Destructor */
    ~EventValue(){} 
    /* Getter function for eventValue */
    int getValue() const; 
private:
    int eventValue; 
};

/***********************************************
                   Event
 * Event has the ownership of EventValue objects 
************************************************/

class Event 
{
public:
    /* Constructor */
    Event(std::string inputType, long inputTimestamp, EventValue* inputEventValue = nullptr); 
    /* Copy-constructor */
    Event(Event const& other); 
    /* Overload assignment operator */
    Event& operator=(Event const& other);
    /* Utility function to transfer all class member data from existing event to new/existing event */
    void dataTransfer(Event const& other);
    /* Destructor */ 
    ~Event(); 
    /* Bool check if object has eventValue - returns true if it does and false otherwise */
    bool hasValue()const; 
    /* Getter function for timestamp */
    long getTimestamp() const; 
    /* Getter function for eventValue object */
    EventValue* getValue() const; 
    /* Getter function for type */
    std::string getType() const; 
    
private:
    long timestamp; 
    std::string type; 
    EventValue* eventValue; // Owned by Ingredient object
};

/***********************************************
                   Roast
 * Roast has the ownership ot Event objects 
 * Roast has the ownership ot Ingredient objects 
************************************************/

class Roast 
{
public:
    /* Constructor */
    Roast(long inputId, long inputBeginTimestamp); 
    /* Copy-constructor */
    Roast(Roast const& other); 
    /* Overload assignment operator */
    Roast& operator=(Roast const& other);
    /* Utility function to transfer all class member data from existing roast to new/existing roast */
    void dataTransfer(Roast const& other);
    /* Destructor */ 
    ~Roast(); 
    /* Getter function for roastId */
    long getId() const; 
    /* Getter function for beginTimeStamp */
    long getTimestamp() const;
    /* Getter function for eventCount */
    int getEventCount() const; 
    /* Getter function for ingredientCount */
    int getIngredientsCount() const;
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
    /* Dynamically allocated array containing pointers to dynamically allocated Event objects */
    const Event* * eventArray = new const Event*[eventArrayCapacity]; // Owned by Roast object
    /* Dynamically allocated array containing pointers to dynamically allocated Ingredient objects */
    const Ingredient* * ingredientArray = new const Ingredient*[ingredientArrayCapacity]; // Owned by Roast object
    
    /* DEAR MARKER
    Ideally, I would implment the above resizable arrays by writing my own templated class
    (or just using std::vector) but since we are not allowed to use templates at all 
    I incooperated the "resizability" into addIngredient() and addEvent(). */
};
