// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


void UShooterAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
}

void UShooterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
    if (ShooterCharacter == nullptr)
    {
        ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
    }

    if (ShooterCharacter)
    {
        FVector Velocity = ShooterCharacter->GetVelocity();
        Velocity.Z = 0.f; // 점프, 추락 등의 속도에 영향을 받지 않음
        Speed = Velocity.Size();

        bIsInAir = ShooterCharacter->GetCharacterMovement()->IsFalling();

        if (ShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
        {
            bIsAccelerating = true;
        }
        else
        {
            bIsAccelerating = false;
        }

        FRotator AimRotation = ShooterCharacter->GetBaseAimRotation();
        FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(ShooterCharacter->GetVelocity());
        MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
        
        if (ShooterCharacter->GetVelocity().Size() > 0.f)
        {
            LastMovementOffsetYaw = MovementOffsetYaw;
        }
        // if (GEngine)
        // {
        //     FString OffsetMessage = FString::Printf(TEXT("Movement Offset Yaw: %f"), AimRotation.Yaw);
        //     GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::White, OffsetMessage);

        //     // FVector InverseTD = ShooterCharacter->GetActorTransform().InverseTransformVectorNoScale(ShooterCharacter->GetVelocity());
        //     // float testF = FRotationMatrix::MakeFromX(InverseTD).Rotator().Yaw;
        //     // FString test = FString::Printf(TEXT("test1: %f / test2: %f"), MovementOffsetYaw, testF);
        //     // GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::White, test);

        // }
    }
}
