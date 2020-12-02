/* Roasty Model Header */

#pragma once

#include <string>

/* Initial array size of 6 is assumed since there are six
events that could take place in any roasting proccess */
#define INITIAL_ARRAY_SIZE 6

/*******************************************************
                          Bean  
********************************************************/

class Bean 
{
public:

    Bean(std::string inputBeanName);

    Bean(Bean const& other); 

    Bean& operator=(Bean const& other); 

    /* Getter function for beanName */
    std::string getName() const; 

    ~Bean(){} 

private:

    std::string beanName; 
};

/*******************************************************
                       Ingredient 
 * Ingredient object has the ownership of bean object
********************************************************/

class Ingredient 
{
public:

    Ingredient(Bean& inputBean, int inputNewAmount); 

    Ingredient(Ingredient const& other); 

    Ingredient& operator=(Ingredient const& other); 

    /* Getter function for amount */
    int getAmount() const; 

    /* Getter function for bean object */
    Bean const& getBean() const;

    /* Destructor that deletes all owned objects
    i.e. Bean object */ 
    ~Ingredient();

private:

    int amount; 
    Bean& bean; // Owned by Ingredient object
     
};

/*******************************************************
                      EventValue  
********************************************************/

class EventValue
{
public:

    EventValue(int inputEventValue); 

    EventValue(EventValue const& other); 

    EventValue& operator=(EventValue const& other);

    /* Getter function for eventValue */
    int getValue() const; 

    ~EventValue(){} 

private:

    int eventValue; 
};

/*******************************************************
                         Event
 * Event object has the ownership of EventValue object 
********************************************************/

class Event 
{
public:

    Event(std::string inputType, long inputTimestamp, EventValue* inputEventValue = nullptr); 

    Event(Event const& other); 

    Event& operator=(Event const& other);

    /* Utility function to transfer *all* class member
     data from existing event to new/existing event */
    void dataTransfer(Event const& other);

    /* Bool check if object has eventValue and
    returns true if it does and false otherwise */
    bool hasValue()const; 

    /* Getter function for timestamp */
    long getTimestamp() const; 

    /* Getter function for eventValue object */
    EventValue* getValue() const; 

    /* Getter function for type */
    std::string getType() const; 
    
    /* Destructor that deletes all owned objects
    i.e. EventValue object */  
    ~Event(); 

private:

    long timestamp; 
    std::string type; 
    EventValue* eventValue; // Owned by Ingredient object
};

/*******************************************************
                         Roast
 * Roast object has the ownership ot Event objects 
 * Roast object has the ownership of Ingredient objects 
********************************************************/

class Roast 
{
public:

    Roast(long inputId, long inputBeginTimestamp); 

    Roast(Roast const& other); 

    Roast& operator=(Roast const& other);

    /* Utility function to transfer *some* class member
    data from existing roast to new/existing roast i.e. 
    roastId, beginTimestamp, eventCount, ingredientCount,
    eventArray and ingredientArray */
    void dataTransfer(Roast const& other); 

    /* Getter function for roastId */
    long getId() const; 

    /* Getter function for beginTimeStamp */
    long getTimestamp() const;

    /* Getter function for eventCount */
    int getEventCount() const; 

    /* Getter function for ingredientCount */
    int getIngredientsCount() const;

    /* Take the owneship of the passed event object
    & take a pointer to it and add it to eventArray */
    void addEvent(const Event& event); 

    /* Take the owneship of the passed ingredient object
    & take a pointer to it and add it to ingredientArray */
    void addIngredient(const Ingredient& ingredient);

    /* Destroy the target event object and take its pointer
    off of eventArray & decrement eventCount by one */
    void removeEventByTimestamp(long eventTimestamp); 

    /* Destroy the target ingredient object and take its pointer
    off of eventArray & decrement eventCount by one */
    void removeIngredientByBeanName(std::string beanName); 

    /* Getter function for a specified event object in eventArray */
    Event const& getEvent(int number) const; 

    /* Getter function for a specified ingredient object in ingredeintArray */
    Ingredient const& getIngredient(int number) const; 

    /* Destructor that deletes all owned objects
    i.e. Event and Ingredient objects */ 
    ~Roast();

private:

    long roastId; 
    long beginTimestamp; 
    int eventCount;
    int ingredientsCount;
    int eventArrayCapacity;
    int ingredientArrayCapacity;

    /* Heap allocated array containing pointers to heap allocated Event objects */
    const Event* * eventArray; // Owned by Roast object

    /* Heap allocated array containing pointers to heap allocated Ingredient objects */
    const Ingredient* * ingredientArray; // Owned by Roast object
    
    /* DEAR MARKER
    Ideally, I would implment the above resizable arrays by writing my own templated class
    (or just using std::vector) but since we are not allowed to use templates at all 
    I incooperated the "resizability" into addIngredient() and addEvent(). */
};
