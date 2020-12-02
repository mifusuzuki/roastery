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

    /* Destructor that deletes all owned objects
    i.e. Bean object */ 
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

    /* Utility function to transfer all class member
     data from existing event to new/existing event */
    void dataTransfer(Event const& other);

    /* Destructor that deletes all owned objects
    i.e. EventValue object */  
    ~Event(); 

    /* Bool check if object has eventValue and
    returns true if it does and false otherwise */
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

    /* Utility function to transfer all class member
    data from existing roast to new/existing roast */
    void dataTransfer(Roast const& other);

    /* Destructor that deletes all owned objects
    i.e. Event and Ingredient objects */ 
    ~Roast(); 

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

private:
    long roastId; 
    long beginTimestamp; 
    int eventCount;
    int ingredientsCount;
    int eventArrayCapacity;
    int ingredientArrayCapacity;

    /* Dynamically allocated array containing pointers to dynamically allocated Event objects */
    const Event* * eventArray; // Owned by Roast object

    /* Dynamically allocated array containing pointers to dynamically allocated Ingredient objects */
    const Ingredient* * ingredientArray; // Owned by Roast object
    
    /* DEAR MARKER
    Ideally, I would implment the above resizable arrays by writing my own templated class
    (or just using std::vector) but since we are not allowed to use templates at all 
    I incooperated the "resizability" into addIngredient() and addEvent(). */
};
