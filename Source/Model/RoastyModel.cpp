/* Roasty Model Implementation */
#include "RoastyModel.hpp"

#include <iostream>
#include <string>

/* ============== Bean ================= */

/* user-defined constructor */
Bean::Bean(std::string inputBeanName) 
{
    beanName = inputBeanName; 
}

std::string Bean::getName() const
{
    return beanName;
}

/* ============== Ingredients ================ */

/* user-defined constructor */
Ingredient::Ingredient(const Bean& inputBean, int inputAmount) 
{
    bean = &inputBean; 
    amount = inputAmount;
}

/* copy-constructor */
Ingredient::Ingredient(Ingredient const& other)
{
    this->bean = new Bean(*other.bean);
    this->amount = other.amount;
}

/* assignment-operator overload */
Ingredient& Ingredient::operator=(Ingredient const& other)
{
    /* check if this and other are the identical */
    if (this == &other)
    {
        return *this;
    }
    /* delete the existing Bean object */
    delete this->bean;
    /* assign new data */
    this->bean = new Bean(*other.bean);
    this->amount = other.amount;
    return *this;
}

Ingredient::~Ingredient()
{
    delete bean;
}

int Ingredient::getAmount() const
{
    return amount;
}

Bean const& Ingredient::getBean() const
{
    return *bean;
}

/* ============== Event Value ================ */

/* user-defined constructor */
EventValue::EventValue(int inputEventValue) 
{
    eventValue = inputEventValue; 
}

int EventValue::getValue() const
{
    return eventValue;
}

/* ============== Event ================ */

/* user-defined constructor */
Event::Event(std::string inputType, long inputTimestamp, EventValue* inputEventValue) 
{
    type = inputType; 
    timestamp = inputTimestamp; 
    eventValue = inputEventValue; 
}

/* copy-constructor */
Event::Event(Event const& other)
{
    this->timestamp = other.timestamp;
    this->type = other.type;
    if (other.eventValue == nullptr)
    {
        eventValue = nullptr;
    }
    else
    {
        this->eventValue = new EventValue(*other.eventValue);
    }
}

/* assignment-operator overload */
Event& Event::operator=(Event const& other)
{
    /* check if this and other are the identical */
    if (this == &other)
    {
        return *this;
    }
    /* assign new data */
    this->timestamp = other.timestamp;
    this->type = other.type;
    if (other.eventValue == nullptr)
    {
        eventValue = nullptr;
    }
    else
    {
        this->eventValue = new EventValue(*other.eventValue);
    }
    return *this;
}

Event::~Event()
{
    delete eventValue;
}

bool Event::hasValue()const
{
    if (eventValue == nullptr)
    {
        return false;
    }
    return true;
}

long Event::getTimestamp() const 
{
    return timestamp;
}

EventValue* Event::getValue() const
{
    return eventValue;
}

std::string Event::getType() const
{
    return type;
}

/* ============== Roasts ================ */

/* user-defined constructor */
Roast::Roast(long inputId, long inputBeginTimestamp) 
{
    roastId = inputId; 
    beginTimestamp = inputBeginTimestamp;
    eventCount = 0;
    ingredientsCount = 0;
}

/* copy-constructor */
Roast::Roast(Roast const& other)
{
    this->roastId = other.roastId; 
    this->beginTimestamp = other.beginTimestamp;
    this->eventCount = other.eventCount;
    this->ingredientsCount = other.ingredientsCount;
    for (auto i=0; i<other.eventCount; i++)
    {
        this->eventArray[i] = new Event(other.getEvent(i));
    }
    for (auto i=0; i<other.ingredientsCount; i++)
    {
        this->ingredientArray[i] = new Ingredient(other.getIngredient(i));
    }
}

/* assignment-operator overload */
Roast& Roast::operator=(Roast const& other)
{
    /* check if this and other are the identical */
    if (this == &other)
    {
        return *this;
    }
    /* delete the existing objects (if any) */
    for (auto i=0; i<(this->eventCount); i++)
    {
        delete this->eventArray[i];
    }
    for (auto i=0; i<(this->ingredientsCount); i++)
    {
        delete this->ingredientArray[i];
    }
    /* assign new data */
    this->eventCount = other.eventCount;
    this->roastId = other.roastId; 
    this->beginTimestamp = other.beginTimestamp;
    this->ingredientsCount = other.ingredientsCount;
    for (auto i=0; i<(this->eventCount); i++)
    {
        this->eventArray[i] = new Event(other.getEvent(i));
    }
    for (auto i=0; i<(this->ingredientsCount); i++)
    {
        this->ingredientArray[i] = new Ingredient(other.getIngredient(i));
    }
    return *this;
}

Roast::~Roast()
{
    /* delete all events */
    for (int i=0; i<eventCount; i++)
    {
        delete eventArray[i];
    }
    delete[] eventArray;
    /* delete all ingredients */
    for (int i=0; i<ingredientsCount; i++)
    {
        delete ingredientArray[i];
    }
    delete[] ingredientArray;
}

long Roast::getId() const
{
    return roastId;
}

int Roast::getIngredientsCount() const 
{
    return ingredientsCount;
}

int Roast::getEventCount() const
{
    return eventCount;
}

long Roast::getTimestamp() const
{
    return beginTimestamp;
}

void Roast::addEvent(const Event& event) 
{
    /* check the identical event does not exit already */
    for (int ptr=0; ptr<eventCount; ptr++)
    {
        if (eventArray[ptr] == &event)
        {
            /* identical event object exits already */
            /* deep copy it and add its address to the array */
            addEvent(*(new Event{event}));
            return;
        }
    }
    
    /* hit the cap limit - double the size of array and transfer data */  
    const Event* * temp;
    if (eventCount >= eventArrayCapacity)
    {
        temp = new const Event*[2*eventArrayCapacity];
        for (int i=0; i<eventArrayCapacity; i++)
        {
            temp[i] = eventArray[i];
        }
        delete[] eventArray;
        eventArrayCapacity *= 2;
        eventArray = temp;
    }

    eventArray[eventCount] = &event; 
    eventCount++;
    return;
}

void Roast::addIngredient(const Ingredient& ingredient)
{
    /* check the identical event does not exit already */
    for (int ptr=0; ptr<ingredientsCount; ptr++)
    {
        if (ingredientArray[ptr] == &ingredient)
        {
            /* identical event object exits already */
            /* deep copy it and add its address to the array */
            addIngredient(*(new Ingredient{ingredient}));
            return;
        }
    }
    /* hit the cap limit - double the size of array and transfer data */  
    const Ingredient* * temp;
    if (ingredientsCount >= ingredientArrayCapacity)
    {
        temp = new const Ingredient*[2*ingredientArrayCapacity];
        for (int i=0; i<ingredientArrayCapacity; i++)
        {
            temp[i] = ingredientArray[i];
        }
        delete[] ingredientArray;
        ingredientArrayCapacity *= 2;
        ingredientArray = temp;
    }

    ingredientArray[ingredientsCount] = &ingredient; 
    ingredientsCount++;
    return;
}

void Roast::removeEventByTimestamp(long eventTimestamp)
{
    for (auto i=0; i<eventCount; i++)
    {
        if ((eventArray[i] != nullptr) && (eventArray[i]->getTimestamp() == eventTimestamp))
        {
            delete eventArray[i];
            eventCount--;
            for (int j=i; j<eventCount; j++)
            {
                /* shift each element one by one */
                eventArray[j] = eventArray[j+1];
                /* set the duplicated pointer at the end of the array to 0 */
                eventArray[j+1] = nullptr;
            }
            break;
        } 
    }
}

void Roast::removeIngredientByBeanName(std::string beanName)
{
    for (auto i=0; i<ingredientsCount; i++)
    {
        if ((ingredientArray[i] != nullptr) && (ingredientArray[i]->getBean().getName() == beanName))
        {
            /* remove this event and replace it with last event in the array*/
            delete ingredientArray[i]; 
            ingredientsCount--;
            for (int j=i; j<ingredientsCount; j++)
            {
                /* shift each element one by one */
                ingredientArray[j] = ingredientArray[j+1];
                /* set the duplicated pointer at the end of the array to 0 */
                ingredientArray[j+1] = nullptr;
            }
        } 
        break;
    }
}

Event const& Roast::getEvent(int number) const
{
    return *eventArray[number];
}

Ingredient const& Roast::getIngredient(int number) const
{
    return *ingredientArray[number];
}


