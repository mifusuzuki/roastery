/* Roasty Model Implementation */

#include "RoastyModel.hpp"

#include <string>


/* ============== Bean ================= */

Bean::Bean(std::string inputBeanName) : 
    beanName(inputBeanName) 
{}

Bean::Bean(Bean const& other) : 
    beanName(other.getName()) 
{}

Bean& 
Bean::operator=(Bean const& other) 
{
    // copy other's bean name 
    this->beanName = other.getName();
    return *this;
}

std::string 
Bean::getName() const
{
    return beanName;
}

/* ============== Ingredients ================ */

Ingredient::Ingredient(Bean& inputBean, int inputAmount) : 
    bean(inputBean), 
    amount(inputAmount) 
{}

Ingredient::Ingredient(Ingredient const& other) : 
    bean(*(new Bean(other.getBean()))), 
    amount(other.getAmount()) 
{}

Ingredient& 
Ingredient::operator=(Ingredient const& other)
{
    // Check if this and other are the identical
    if (this == &other)
    {
        return *this;
    }
    // Delete the existing Bean object 
    delete &this->bean;
    // Assign new data 
    this->bean = *(new Bean(other.getBean()));
    this->amount = other.getAmount();

    return *this;
}

int 
Ingredient::getAmount() const
{
    return amount;
}

Bean const& 
Ingredient::getBean() const
{
    return bean;
}

Ingredient::~Ingredient()
{
    delete &bean;
}

/* ============== Event Value ================ */

EventValue::EventValue(int inputEventValue) : 
    eventValue(inputEventValue) 
{}

EventValue::EventValue(EventValue const& other) : 
    eventValue(other.getValue()) 
{}

EventValue& 
EventValue::operator=(EventValue const& other) 
{
    // Assign new data 
    this->eventValue = other.getValue();
    return *this;
}

int 
EventValue::getValue() const
{
    return eventValue;
}

/* ============== Event ================ */

Event::Event(std::string inputType, long inputTimestamp, EventValue* inputEventValue) :
    type(inputType),
    timestamp(inputTimestamp),
    eventValue(inputEventValue) 
{}

Event::Event(Event const& other)
{
    // Assign other's data to this object 
    dataTransfer(other);
}

Event& 
Event::operator=(Event const& other)
{
    //Check if this and other are the identical 
    if (this == &other)
    {
        return *this;
    }
    // Delete the existing EventValue object
    if (other.hasValue())
    {
        delete other.getValue();
    }
    // Copy over other's data to this object 
    dataTransfer(other); 

    return *this;
}

void 
Event::dataTransfer(Event const& other)
{
    // Copy timestamp, type and eventValue
    this->timestamp = other.getTimestamp();
    this->type = other.getType();
    if (other.hasValue())
    {
        this->eventValue = new EventValue(*other.getValue());
    }
    else
    {
        eventValue = nullptr;
    }
}

bool 
Event::hasValue()const
{
    if (eventValue == nullptr)
    {
        return false;
    }
    return true;
}

long 
Event::getTimestamp() const 
{
    return timestamp;
}

EventValue* 
Event::getValue() const
{
    return eventValue;
}

std::string 
Event::getType() const
{
    return type;
}

Event::~Event()
{
    delete eventValue;
}

/* ============== Roasts ================ */

Roast::Roast(long inputId, long inputBeginTimestamp) :

    roastId(inputId), 
    beginTimestamp(inputBeginTimestamp)
    
{   
    // Assign initial values and create heap allocated arrays 
    eventCount = 0;
    ingredientsCount = 0;
    eventArrayCapacity = INITIAL_ARRAY_SIZE;
    ingredientArrayCapacity = INITIAL_ARRAY_SIZE;
    eventArray = new const Event*[eventArrayCapacity];
    ingredientArray = new const Ingredient*[ingredientArrayCapacity];
}

Roast::Roast(Roast const& other)
{
    // Assign initial values and create heap allocated arrays 
    // to prepare for creating a copy of "other"
    this->eventArrayCapacity = INITIAL_ARRAY_SIZE;
    this->ingredientArrayCapacity = INITIAL_ARRAY_SIZE;
    this->eventArray = new const Event*[eventArrayCapacity];
    this->ingredientArray = new const Ingredient*[ingredientArrayCapacity];
    // Assign other's data to this object 
    dataTransfer(other);
}

Roast& 
Roast::operator=(Roast const& other)
{
    // Check if this and other are the identical 
    if (this == &other)
    {
        return *this;
    }
    // Delete the existing objects in the existing event array
    for (auto i=0; i<(this->eventCount); i++)
    {
        delete this->eventArray[i];
    }
    // Delete the existing objects in the existing ingredient array
    for (auto i=0; i<(this->ingredientsCount); i++)
    {
        delete this->ingredientArray[i];
    }
    // Copy over other's data to this object 
    dataTransfer(other);

    return *this;
}

void 
Roast::dataTransfer(Roast const& other)
{
    // copy roastId and beginTimestamp
    this->roastId = other.getId(); 
    this->beginTimestamp = other.getTimestamp();
    // Set/reset the counters to 0
    this->eventCount = 0;
    this->ingredientsCount = 0;
    // Copy eventArray elements one by one
    for (auto i=0; i<(other.getEventCount()); i++)
    {
        // addEvent() will add the pointer to the newly created  
        // object to eventArray and increment eventCount by one
        this->addEvent(*(new Event(other.getEvent(i))));
    }
    // Copy ingredientArray elements one by one
    for (auto i=0; i<(other.getIngredientsCount()); i++)
    {
        // addIngredient() will add the pointers to the newly created 
        // object to ingredientArray and increment ingredientCount by one
        this->addIngredient(*(new Ingredient(other.getIngredient(i))));
    }
}

long 
Roast::getId() const
{
    return roastId;
}

long 
Roast::getTimestamp() const
{
    return beginTimestamp;
}

int 
Roast::getEventCount() const
{
    return eventCount;
}

int 
Roast::getIngredientsCount() const 
{
    return ingredientsCount;
}

void 
Roast::addEvent(const Event& event) 
{
    // Check the identical event does not exit already 
    for (int ptr=0; ptr<eventCount; ptr++)
    {
        if (eventArray[ptr] == &event)
        {
            // Identical event object exits already 
            return;
        }
    }
    
    // Hit the cap limit - double the size of array and transfer data 
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
        temp = nullptr;
    }

    // Add a pointer to event to the array and increment the counter
    eventArray[eventCount] = &event; 
    eventCount++;
    return;
}

void 
Roast::addIngredient(const Ingredient& ingredient)
{
    // Check the identical event does not exit already 
    for (int ptr=0; ptr<ingredientsCount; ptr++)
    {
        if (ingredientArray[ptr] == &ingredient)
        {
            // Identical event object exits already 
            return;
        }
    }

    // Hit the cap limit - double the size of array and transfer data 
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
        temp = nullptr;
    }

    // Add a pointer to ingredient to the array and increment the counter
    ingredientArray[ingredientsCount] = &ingredient; 
    ingredientsCount++;
    return;
}

void 
Roast::removeEventByTimestamp(long eventTimestamp)
{
    for (auto i=0; i<eventCount; i++)
    {
        if ((eventArray[i] != nullptr) && (eventArray[i]->getTimestamp() == eventTimestamp))
        {
            /* 
            TASK - Remove this event and replace it with last event in the array
            SOFT ASSUMPTION - There wont be too many elements 
            in the array to cause too much computational inefficiency 
            ALTERNATIVE SOLUTION - Take the last element and replace 
            the removed element and decrement the counter by one 
            */
            delete eventArray[i];
            eventCount--;
            for (int j=i; j<eventCount; j++)
            {
                // Shift each element one by one 
                eventArray[j] = eventArray[j+1];
                // Set the duplicated pointer at the end of the array to 0 
                eventArray[j+1] = nullptr;
            }
            break;
        } 
    }
    return;
}

void 
Roast::removeIngredientByBeanName(std::string beanName)
{
    for (auto i=0; i<ingredientsCount; i++)
    {
        if ((ingredientArray[i] != nullptr) && (ingredientArray[i]->getBean().getName() == beanName))
        {
            /* 
            TASK - Remove this ingredient and replace it with last event in the array
            SOFT ASSUMPTION - There wont be too many elements 
            in the array to cause too much computational inefficiency 
            ALTERNATIVE SOLUTION - Take the last element and replace 
            the removed element and decrement the counter by one 
            */
            delete ingredientArray[i]; 
            ingredientsCount--;
            for (int j=i; j<ingredientsCount; j++)
            {
                // Shift each element one by one 
                ingredientArray[j] = ingredientArray[j+1];
                // Set the duplicated pointer at the end of the array to 0 
                ingredientArray[j+1] = nullptr;
            }
        } 
        break;
    }
    return;
}

Event const& 
Roast::getEvent(int number) const
{
    return *eventArray[number];
}

Ingredient const& 
Roast::getIngredient(int number) const
{
    return *ingredientArray[number];
}

Roast::~Roast()
{
    // Delete all heap allocated events and the array 
    for (int i=0; i<eventCount; i++)
    {
        delete eventArray[i];
    }
    delete[] eventArray;
    // Delete all heap allocated ingredients and the array 
    for (int i=0; i<ingredientsCount; i++)
    {
        delete ingredientArray[i];
    }
    delete[] ingredientArray;
}
