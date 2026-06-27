#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <vector>
#include "item.h"
#include "dice.h"
#include "user_interface.h"
using namespace std;

struct Character;

// ---------- State Pattern ----------
class CharacterState
{
public:
    virtual ~CharacterState() = default;
    virtual void HandleAction(Character& character, Character& other) = 0;
    virtual void HandleChangeState(Character& character);
};

class BasicAttackState : public CharacterState
{
public:
    void HandleAction(Character& character, Character& other) override;
};

class SpecialAttackState : public CharacterState
{
public:
    void HandleAction(Character& character, Character& other) override;
};

class InventoryState : public CharacterState
{
public:
    void HandleAction(Character& character, Character& other) override;
};

class HealState : public CharacterState
{
public:
    void HandleAction(Character& character, Character& other) override;
};

class FleeState : public CharacterState
{
public:
    void HandleAction(Character& character, Character& other) override;
};

class CharacterContext
{
private:
    CharacterState* state;
public:
    CharacterContext();
    void SetState(CharacterState* newState);
    void Execute(Character& character, Character& other);
};

struct Characteristics
{
    int strength, dexterity, constitution, wisdom, intelligence, charisma, armorClass;
    Characteristics();
    Characteristics(int,int,int,int,int,int,int);
    int CountModificator(int characteristic);
    void PrintCharacteristics();
};

struct Appearance
{
    string skinColor;
    string hairColor;
};

struct Character
{
    string name;
    Appearance appearance;

    int health, maxHealth, healthFlasks;
    int damageFace, specialCooldown;
    int gold;

    vector<Item> inventory;
    Characteristics characteristics;

    int uniqueAbilityDifficulty;
    bool minionSpawned = false;
    Character* minion = nullptr;

    Character();
    Character(string,int,int,int,int,Character&,int);
    Character(string,int,int,int,int);

    void PrintStatus();
    void RemoveGold(int amount);
    void AddGold(int amount);
    bool BuyItem(int cost);

    void BasicAttack(Character& other);
    void SpecialAttack();
    void ShowInventory();
    void IncreaseHealth(int amount);
    void DecreaseHealth(int amount);
    void Heal(int difficulty);
    bool Flee(Character& other);
    bool CheckFleeSuccess(int difficulty);
};

#endif
