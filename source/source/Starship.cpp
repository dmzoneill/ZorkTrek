#include "Starship.h"


/**
 * Constructor
 *
 * @param name the name of the starship
 */

StarShip::StarShip(string name, int gameDifficulty)
{
	this->name = name;
	
	this->hasTractorLock = false;

	this->food = 300;
	this->water = 300;
	this->plasma = 300;
	this->trianium = 300;
	this->dilithium = 300;

	this->power = 500;
	
	this->photons = 99;
	this->quantums = 25;
	this->shields = 200;
	this->armour = 400;
	this->isWreck = false;
	this->enginesRepaired = false;

	this->cargohold = ((food * FOOD_WEIGHT) + (water * WATER_WEIGHT) + (plasma * PLASMA_WEIGHT) + (trianium * TRIANIUM_WEIGHT) + (dilithium * DILITHIUM_WEIGHT));	

	switch(gameDifficulty)
	{
		case 1:
			this->shieldRegenRate = 10;
		break;

		case 2:
			this->shieldRegenRate = 8;
		break;

		case 3:
			this->shieldRegenRate = 6;
		break;

		case 4:
			this->shieldRegenRate = 4;
		break;

		case 5:
			this->shieldRegenRate = 2;
		break;

		default:
			this->shieldRegenRate = 2;

	}

	/**
	  * thread (Output) Pthread handle to the created thread
	  * attr (Input) The thread attributes object containing the attributes to be associated with the newly created thread. If NULL, the default thread attributes are used.
      * start_routine (Input) The function to be run as the new threads start routine
      * arg * (Input) An address for the argument for the threads start routine
	  */

	this->shieldThreadRunning = true;
	pthread_create( &this->shieldThread, NULL, &StarShip::shieldRegenThread, this );

}


/**
 * destructor
 */

StarShip::~StarShip()
{

	/* kill the shield regeneration thread if its running */
	if(this->shieldThreadRunning==true)
	{
		int y = pthread_kill(this->shieldThread, 0);
	}

	cout << "             ~Deconstructing Starship " << endl;
}


/**
 * Entry point for the shield regeneration thread
 *
 * @param void pointer (can be pointed at anything) (this)
 *
 * @return void
 */

void *StarShip::shieldRegenThread(void *ptr)
{
	// critical section
	while(1)
	{
		if(((StarShip *)ptr)->getShieldStrenght()<MAX_SHIELDS)
		{
			((StarShip *)ptr)->setShieldStrenght(((StarShip *)ptr)->getShieldStrenght() + ((StarShip *)ptr)->getShieldRegenerativeRate());
		}
		sleep(5);
	}
}


/**
 * Accessor for the name of the starship
 *
 * @return string
 */

string StarShip::getName()
{
	return this->name;
}


/**
 * Accessor for the ships shield strenght
 *
 * @return int
 */

int StarShip::getShieldStrenght()
{
	return this->shields;
}


/**
 * Accessor for the regenerative rate of the ships shields
 *
 * @return int
 */

int StarShip::getShieldRegenerativeRate()
{
	return this->shieldRegenRate;
}


/**
 * Accessor for the ships armour
 *
 * @return int
 */

int StarShip::getArmour()
{
	return this->armour;
}


/**
 * Accessor for the ships armour
 *
 * @return int
 */

bool StarShip::getHasTractorLock()
{
	return this->hasTractorLock;
}


/**
 * Accessor for the ships photons
 *
 * @return int
 */

int StarShip::getPhotons()
{
	return this->photons;
}


/**
 * Accessor for the ships quantums
 *
 * @return int
 */

int StarShip::getQuantums()
{
	return this->quantums;
}


/**
 * Accessor for the ships power
 *
 * @return int
 */

int StarShip::getPower()
{
	return this->power;
}


/**
 * Accessor for the ships state
 *
 * @return bool
 */

bool StarShip::getIsWreck()
{
	return this->isWreck;
}


/**
 * Mutator for the ships armour
 *
 * @param strength
 *
 * @return void
 */

void StarShip::setShieldStrenght(int strenght)
{
	this->shields = strenght;
}


/**
 * Mutator for the ships shield regnerative rate
 *
 * @param rate
 *
 * @return void
 */

void StarShip::setShieldRegenerativeRate(int rate)
{
	this->shieldRegenRate = rate;
}


/**
 * Mutator for the ships armour
 *
 * @param armour
 *
 * @return void
 */

void StarShip::setArmour(int armour)
{
	this->armour = armour;
}


/**
 * Mutator for the ships photons
 *
 * @param num
 *
 * @return void
 */

void StarShip::setPhotons(int num)
{
	this->photons = num;
}


/**
 * Mutator for the ships quantums
 *
 * @param num
 *
 * @return void
 */

void StarShip::setQuantums(int num)
{
	this->quantums = num;
}


/**
 * Mutator for the ships tractor lock
 *
 * @param has
 *
 * @return void
 */

void StarShip::setHasTractorLock(bool has)
{
	this->hasTractorLock = has;
}


/**
 * Mutator for the ships status
 *
 * @return void
 */

void StarShip::setWreck()
{
	this->isWreck = true;
}


/**
 * Mutator for the ships power
 *
 * @param num
 *
 * @return void
 */

void StarShip::setPower(int num)
{
	this->power = num;
}


/**
 * Accessor for the ships food
 *
 * @return int
 */

int StarShip::getFood()
{
	return this->food;
}


/**
 * Accessor for the ships water
 *
 * @return int
 */

int StarShip::getWater()
{
	return this->water;
}


/**
 * Accessor for the ships plasma
 *
 * @return int
 */

int StarShip::getPlasma()
{
	return this->plasma;
}


/**
 * Accessor for the ships trianium
 *
 * @return int
 */

int StarShip::getTrianium()
{
	return this->trianium;
}


/**
 * Accessor for the ships dilithium
 *
 * @return int
 */

int StarShip::getDilithium()
{
	return this->dilithium;
}


/**
 * Accessor for the ships cargo max weight
 *
 * @return int
 */

int StarShip::getCargoWeight()
{
	return this->cargohold;
}


/**
 * Accessor for the ships cargo weight
 *
 * @return int
 */

int StarShip::usage()
{
	return ((this->food * FOOD_WEIGHT) + (this->water * WATER_WEIGHT) + (this->plasma * PLASMA_WEIGHT) + (this->trianium * TRIANIUM_WEIGHT) + (this->dilithium * DILITHIUM_WEIGHT));
}


/**
 * Mutator for the ships food
 * Wont allow more than the max cargo weight
 *
 * @param val
 *
 * @return void
 */

void StarShip::setFood(int val)
{
	int available = CARGOHOLD_MAX_WEIGHT - ((this->food * FOOD_WEIGHT) + (this->water * WATER_WEIGHT) + (this->plasma * PLASMA_WEIGHT) + (this->trianium * TRIANIUM_WEIGHT) + (this->dilithium * DILITHIUM_WEIGHT));

	if((CARGOHOLD_MAX_WEIGHT - this->usage()) > 0 )
	{
		int spaceRequired = (val * FOOD_WEIGHT) - (this->food * FOOD_WEIGHT);
		if((this->usage() + spaceRequired) >= CARGOHOLD_MAX_WEIGHT)
		{
			this->food = this->food + (available / FOOD_WEIGHT);
			cout << "             Sir, we were able to beam up " << (available / FOOD_WEIGHT) << " units of food, cargohold is now full";
		}
		else
		{
			cout << "             Sir, we were able to beam up " << (val - this->food) << " units of food";
			this->water = val;
		}				
	}
	else
	{
		cout << "             Sir, the cargohold is full";
		// not enough space
	}	
	cout << endl;

	this->updateCargoWeight();
}


/**
 * Mutator for the ships water
 * Wont allow more than the max cargo weight
 *
 * @param val
 *
 * @return void
 */

void StarShip::setWater(int val)
{		
	int available = CARGOHOLD_MAX_WEIGHT - ((this->food * FOOD_WEIGHT) + (this->water * WATER_WEIGHT) + (this->plasma * PLASMA_WEIGHT) + (this->trianium * TRIANIUM_WEIGHT) + (this->dilithium * DILITHIUM_WEIGHT));

	if((CARGOHOLD_MAX_WEIGHT - this->usage()) > 0 )
	{
		int spaceRequired = (val * WATER_WEIGHT) - (this->water * WATER_WEIGHT);
		if((this->usage() + spaceRequired) >= CARGOHOLD_MAX_WEIGHT)
		{
			this->water = this->water + (available / WATER_WEIGHT);
			cout << "             Sir, we were able to beam up " << (available / WATER_WEIGHT) << " units of water, cargohold is now full";
		}
		else
		{
			cout << "             Sir, we were able to beam up " << (val - this->water) << " units of water";
			this->water = val;
		}				
	}
	else
	{
		cout << "             Sir, the cargohold is full";
		// not enough space
	}	
	cout << endl;

	this->updateCargoWeight();
}


/**
 * Mutator for the ships plasma
 * Wont allow more than the max cargo weight
 *
 * @param val
 *
 * @return void
 */

void StarShip::setPlasma(int val, bool transporter)
{
	if(!transporter)
	{
		this->plasma = val;
		this->updateCargoWeight();
		return;
	}

	int available = CARGOHOLD_MAX_WEIGHT - ((this->food * FOOD_WEIGHT) + (this->water * WATER_WEIGHT) + (this->plasma * PLASMA_WEIGHT) + (this->trianium * TRIANIUM_WEIGHT) + (this->dilithium * DILITHIUM_WEIGHT));

	if((CARGOHOLD_MAX_WEIGHT - this->usage()) > 0 )
	{
		int spaceRequired = (val * PLASMA_WEIGHT) - (this->plasma * PLASMA_WEIGHT);
		if((this->usage() + spaceRequired) >= CARGOHOLD_MAX_WEIGHT)
		{
			this->plasma = this->plasma + (available / PLASMA_WEIGHT);
			cout << "             Sir, we were able to beam up " << (available / PLASMA_WEIGHT) << " units of plasma, cargohold is now full";
		}
		else
		{
			cout << "             Sir, we were able to beam up " << (val - this->plasma) << " units of plasma";
			this->plasma = val;
		}				
	}
	else
	{
		cout << "             Sir, the cargohold is full";
		// not enough space
	}	
	cout << endl;

	this->updateCargoWeight();
}


/**
 * Mutator for the ships trianium
 * Wont allow more than the max cargo weight
 *
 * @param val
 *
 * @return void
 */

void StarShip::setTrianium(int val)
{
	int available = CARGOHOLD_MAX_WEIGHT - ((this->food * FOOD_WEIGHT) + (this->water * WATER_WEIGHT) + (this->plasma * PLASMA_WEIGHT) + (this->trianium * TRIANIUM_WEIGHT) + (this->dilithium * DILITHIUM_WEIGHT));

	if((CARGOHOLD_MAX_WEIGHT - this->usage()) > 0 )
	{
		int spaceRequired = (val * TRIANIUM_WEIGHT) - (this->trianium * TRIANIUM_WEIGHT);
		if((this->usage() + spaceRequired) >= CARGOHOLD_MAX_WEIGHT)
		{
			this->trianium = this->trianium + (available / TRIANIUM_WEIGHT);
			cout << "             Sir, we were able to beam up " << (available / TRIANIUM_WEIGHT) << " units of trianium, cargohold is now full";
		}
		else
		{
			cout << "             Sir, we were able to beam up " << (val - this->trianium) << " units of trianium";
			this->trianium = val;
		}				
	}
	else
	{
		cout << "             Sir, the cargohold is full";
		// not enough space
	}	
	cout << endl;

	this->updateCargoWeight();
}


/**
 * Mutator for the ships dilithium
 * Wont allow more than the max cargo weight
 *
 * @param val
 *
 * @return void
 */

void StarShip::setDilithium(int val)
{
	int available = CARGOHOLD_MAX_WEIGHT - ((this->food * FOOD_WEIGHT) + (this->water * WATER_WEIGHT) + (this->plasma * PLASMA_WEIGHT) + (this->trianium * TRIANIUM_WEIGHT) + (this->dilithium * DILITHIUM_WEIGHT));

	if((CARGOHOLD_MAX_WEIGHT - this->usage()) > 0 )
	{
		int spaceRequired = (val * DILITHIUM_WEIGHT) - (this->dilithium * DILITHIUM_WEIGHT);
		if((this->usage() + spaceRequired) >= CARGOHOLD_MAX_WEIGHT)
		{
			this->dilithium = this->dilithium + (available / DILITHIUM_WEIGHT);
			cout << "             Sir, we were able to beam up " << (available / DILITHIUM_WEIGHT) << " units of dilithium, cargohold is now full";
		}
		else
		{
			cout << "             Sir, we were able to beam up " << (val - this->dilithium) << " units of dilithium";
			this->dilithium = val;
		}				
	}
	else
	{
		cout << "             Sir, the cargohold is full";
		// not enough space
	}	
	cout << endl;

	this->updateCargoWeight();
}


/**
 * Updates teh cargo weight based on the cargohold items
 *
 * @return void
 */

void StarShip::updateCargoWeight()
{
	this->cargohold = (this->food * FOOD_WEIGHT) + (this->water * WATER_WEIGHT) + (this->plasma * PLASMA_WEIGHT) + (this->trianium * TRIANIUM_WEIGHT) + (this->dilithium * DILITHIUM_WEIGHT);
}
	


/**
 * Repairs the ships engines if you have enough resources
 *
 * @return void
 */

void StarShip::repair()
{
	if(this->trianium >= REPAIR_NEEDED_TRIANIUM && this->dilithium >= REPAIR_NEEDED_DILITHIUM)
	{
		cout << endl << "             Sir, we have repaired the ships trans warp drive" << endl;
		this->trianium = this->trianium - REPAIR_NEEDED_TRIANIUM;
		this->dilithium = this->dilithium - REPAIR_NEEDED_DILITHIUM;
		this->enginesRepaired = true;
	}
	else
	{
		cout << endl << "             Sir, we don't have enough resources to repair the ships trans warp drive" << endl;
	}
}

