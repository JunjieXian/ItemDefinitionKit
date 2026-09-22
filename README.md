# ItemDefinitionKit

A reusable Unreal Engine 5 plugin that provides a data-driven **item definition** system based on **fragments**, **actions**, and **runtime instances**.

Inspired by composition-style item frameworks (similar in spirit to Lyra / Gameplay Inventory patterns), it lets you author items as abstract definition classes composed of small, instanced fragments—rather than deep inheritance trees.

## Requirements

- Unreal Engine **5.0+**
- Modules: `Core`, `CoreUObject`, `Engine`, `GameplayTags`, `Slate`, `SlateCore`

## Features

- **Item definitions** (`UItemDefinition`) — display data + fragment list
- **Fragments** (`UItemFragment`) — composable capability / data slices (mesh, interact, etc.)
- **Actions** (`UItemAction`) — reusable behaviors executed by fragments (e.g. play sound on use)
- **Runtime instances** (`UItemInstance`) — live item objects with GameplayTag-based float attributes
- **Blueprint-friendly** APIs for construction, attribute access, and fragment lookup

---

## Plugin Structure

```
ItemDefinitionKit/
├── ItemDefinitionKit.uplugin
├── Resources/
│   └── Icon128.png
└── Source/
    └── ItemDefinitionKit/
        ├── ItemDefinitionKit.Build.cs
        ├── Public/
        │   ├── ItemDefinitionKit.h          # Module interface
        │   ├── ItemDefinition.h             # Authoring definition (abstract)
        │   ├── ItemInstance.h               # Runtime item instance
        │   ├── ItemFunctionLibrary.h        # Blueprint helpers
        │   ├── Fragments/
        │   │   ├── ItemFragment.h
        │   │   ├── ItemFragment_StaticMesh.h
        │   │   ├── ItemFragment_SkeletalMesh.h
        │   │   └── ItemFragment_InteractUsable.h
        │   └── Actions/
        │       ├── ItemAction.h
        │       ├── ItemAction_PlaySound2D.h
        │       └── ItemAction_PlaySoundAtLocation.h
        └── Private/
            └── ... (matching .cpp implementations)
```

### Core Concepts

| Type | Role |
|------|------|
| `UItemDefinition` | Static/authoring data for an item type (CDO). Holds name, description, and instanced fragments. |
| `UItemFragment` | Optional data/behavior slice attached to a definition. Called when an instance is created. |
| `UItemAction` | Executable behavior unit (BlueprintNativeEvent). Used by fragments such as InteractUsable. |
| `UItemInstance` | Runtime object: references a definition class + `TMap<FGameplayTag, float>` attributes. |
| `UItemFunctionLibrary` | Convenience factory to create and initialize instances. |

```
UItemDefinition (authoring)
 └── ItemFragments[] ──► UItemFragment (+ subclasses)
                              └── (e.g.) OnUseActions[] ──► UItemAction

UItemInstance (runtime)
 ├── ItemDefinition ──► TSubclassOf<UItemDefinition>
 └── ItemAttributes ──► TMap<FGameplayTag, float>
```

---

## Installation

1. Copy or clone this repository into your project's `Plugins/` folder:

   ```text
   YourProject/Plugins/ItemDefinitionKit/
   ```

2. Enable **ItemDefinitionKit** in **Edit → Plugins**, or ensure it is listed in your `.uproject` plugins array.

3. Add a module dependency in your game module's `Build.cs`:

   ```csharp
   PublicDependencyModuleNames.AddRange(new[]
   {
       "ItemDefinitionKit",
       "GameplayTags",
   });
   ```

4. Regenerate project files and compile.

---

## Quick Start

### 1. Create an Item Definition

1. In the Content Browser, create a Blueprint class based on **`ItemDefinition`** (abstract).
2. Set **Item Name** and **Item Description**.
3. Under **Fragments**, add one or more fragment instances (Edit Inline):
   - `ItemFragment_StaticMesh` — static mesh reference
   - `ItemFragment_SkeletalMesh` — skeletal mesh + animation options
   - `ItemFragment_InteractUsable` — list of `OnUseActions` to run on interact/use

### 2. Create a Runtime Instance (Blueprint)

Use **Construct Item Instance Initialize** from `Item Function Library`:

| Pin | Description |
|-----|-------------|
| `Item Definition` | Subclass of `UItemDefinition` |
| `Init Attributes` | Optional map of GameplayTags → float (recommended under `Item.Attributes`) |
| `Outer` | Owning object (defaults to self when called from an actor/object context) |

This creates a `UItemInstance`, assigns the definition, notifies all fragments via `OnInstanceCreated`, then applies initial attributes.

### 3. Create a Runtime Instance (C++)

```cpp
#include "ItemFunctionLibrary.h"
#include "ItemInstance.h"

TMap<FGameplayTag, float> InitAttributes;
InitAttributes.Add(FGameplayTag::RequestGameplayTag(TEXT("Item.Attributes.Durability")), 100.f);

UItemInstance* Instance = UItemFunctionLibrary::ConstructItemInstanceInitialize(
    MyItemDefinitionClass,
    InitAttributes,
    this /* Outer */);
```

### 4. Look Up Fragments

**From a definition class (static):**

```cpp
const UItemFragment* Frag = UItemDefinition::FindFragmentByClass(
    MyItemDefinitionClass,
    UItemFragment_StaticMesh::StaticClass());
```

**From an instance:**

```cpp
const UItemFragment* Frag = Instance->FindFragmentByClass(
    UItemFragment_StaticMesh::StaticClass());
```

In Blueprint, both paths expose **Find Fragment By Class** with automatic output typing.

### 5. Interact / Use an Item

If the definition includes `UItemFragment_InteractUsable`:

1. Resolve the fragment with `FindFragmentByClass`.
2. Call **`InteractUse(ItemOwner, ItemInstance)`**.
3. Each action in `OnUseActions` runs `Execute`. Returns `true` if **any** action succeeds.

Built-in actions:

- **`ItemAction_PlaySound2D`** — plays a 2D sound via `UGameplayStatics::PlaySound2D`
- **`ItemAction_PlaySoundAtLocation`** — plays a spatial sound at a configured location/rotation

You can subclass `UItemAction` (C++ or Blueprint) and override `Execute` for custom behavior (heal, spawn FX, consume, etc.).

### 6. Runtime Attributes

```cpp
Instance->SetAttributeValue(SomeTag, 42.f);
float Value = Instance->GetAttributeValue(SomeTag); // 0 if missing
```

Attribute tags are intended to live under the **`Item.Attributes`** category (enforced via meta on the Blueprint API).

---

## Extending the Kit

### Custom Fragment

```cpp
UCLASS()
class UItemFragment_MyData : public UItemFragment
{
    GENERATED_BODY()
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float Foo = 0.f;

    virtual void OnInstanceCreated_Implementation(UItemInstance* ItemInstance) override
    {
        // Seed instance attributes, register listeners, etc.
    }
};
```

### Custom Action

```cpp
UCLASS()
class UItemAction_MyBehavior : public UItemAction
{
    GENERATED_BODY()
public:
    virtual bool Execute_Implementation(AActor* ItemOwner, UItemInstance* ItemInstance) override
    {
        // Return true on success
        return true;
    }
};
```

Add your custom fragment/action classes to a definition’s instanced arrays in the editor.

---

## API Reference (Summary)

### `UItemDefinition`

- `ItemName`, `ItemDescription` — display text
- `ItemFragments` — instanced fragment array
- `FindFragmentByClass(ItemDefinition, FragmentClass)` — search CDO fragments

### `UItemInstance`

- `Initialize(ItemDef, InitAttributes)` — bind definition, notify fragments, set attributes
- `GetAttributeValue` / `SetAttributeValue`
- `FindFragmentByClass`

### `UItemFragment`

- `OnInstanceCreated(ItemInstance)` — BlueprintNativeEvent hook on instance creation

### `UItemFragment_InteractUsable`

- `OnUseActions` — instanced actions
- `InteractUse(ItemOwner, ItemInstance)` — execute actions; success if any returns true

### `UItemAction`

- `Execute(ItemOwner, ItemInstance)` — BlueprintNativeEvent; default implementation returns `true`

### `UItemFunctionLibrary`

- `ConstructItemInstanceInitialize(ItemDefinition, InitAttributes, Outer)`

---

## Design Notes

- Definitions are **`Abstract` + `Const`** — intended as Blueprintable class defaults (CDO), not mutable runtime objects.
- Fragments and actions use **`DefaultToInstanced` + `EditInlineNew`** so designers can compose them inline on the definition.
- This plugin focuses on **definition / instance / fragment / action** plumbing. Inventory containers, networking, save-game, and UI are left to your game modules.

## License

Copyright © Kay (JunjieXian). All rights reserved unless otherwise stated by the repository owner.

## Author

**JunjieXian**
