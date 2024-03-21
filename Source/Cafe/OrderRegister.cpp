// Fill out your copyright notice in the Description page of Project Settings.


#include "OrderRegister.h"

// Sets default values
AOrderRegister::AOrderRegister()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AOrderRegister::Interact_Implementation() {

	IsFulfilled();
}