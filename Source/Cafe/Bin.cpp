// Fill out your copyright notice in the Description page of Project Settings.


#include "Bin.h"

// Sets default values
ABin::ABin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ABin::Interact_Implementation() {
	
	ClearTicket();
}

