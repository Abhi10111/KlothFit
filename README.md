# Unreal-Based Virtual Try-On Pipeline (Technical Assignment)

## Assignment Objective

The goal of this assignment is to **simulate a end-to-end pipeline** where:

1. A user uploads an image (body / person reference) via frontend
2. Backend processes the input
3. Unreal Engine generates an **updated output image**
   - With modified clothing
   - With body-fit adjustments
4. The final rendered image is returned to the user

This repository focuses on the **Unreal side of the pipeline**.

---

## Approach

A key early observation was that **collision alone is insufficient** for cloth fitting:

- Unreal colliders are repulsive.
- They lack contextual awareness (e.g. sleeves vs torso, waist vs hips)
- Collision-based fitting cannot infer *where* cloth should wrap or stretch.

To achieve contextual awareness, **rigging is required**.

Keeping this in mind two parallel ideas were explored.
### 1. Rigging + Colliders

- Both the human model and fabric are authored around the **same skeletal rig** (Blender / Maya).
- The shared rig provides contextual awareness (e.g. sleeves follow arms).
- In Unreal:
  - Colliders are added around the skeletal mesh
  - Collider sizes are adjusted to simulate different body shapes
  - The fabric is simulated as cloth on the same skeletal mesh, allowing it to:
    - Stretch
    - Wrap
    - Adjust based on collider dimensions

This approach relies on physics-based clothing response guided by colliders on the skeletal mesh.

![alt text](image.png)
### 2. MetaHuman-Based Character Setup

- Evaluated Unreal's built-in cloth resizing pipeline as an offline renderer.
- Cloth is rigged to the MetaHuman skeletal mesh, providing strong contextual awareness(Unreal).
- MetaHuman tooling allows body and outfit sizing via **editor-controlled parameters and presets**.
- Cloth resizing, wrapping, and drape are handled internally by Unreal’s MetaHuman system.

This approach produced **very accurate fitting results** with minimal manual tuning.
Video demonstranting automatic resizing:
https://drive.google.com/file/d/182bQzf0-h3VWifidQN93ySsnNS8IxmPR/view?usp=sharing

---

## Major Constraints Identified

Both approaches were validated manually, but a fully automated end-to-end solution is currently limited by the following constraints.

### 1. Rigging + Colliders

- Fitting accuracy is highly sensitive to **initial rig and weight painting**.
- Accurate mapping must be done **per fabric type and size**.
- Auto-rigging tools were evaluated:
  - Worked well for human skeletal meshes
  - Produced inaccurate mappings for clothing
- This approach remains viable, but would require:
  - Improved cloth-specific auto-rigging
  - More time for high-quality weight transfer

### 2. MetaHuman-Based Character Setup

- Manual results are excellent:
  - Low sensitivity to initial rigging
  - Fast setup
  - High-quality cloth resizing
- However:
  - MetaHuman creation and body modification are **cloud-based**
  - Unreal does **not expose APIs** to programmatically modify body parameters
  - Model and fabric size changes can only be performed via the Unreal Editor UI
  - Runtime or headless modification is not supported

This makes full automation infeasible using MetaHuman alone.

---

## Repository Structure

### Frontend
- Contains files representing user input.
- Currently implemented as a JSON file specifying:
  - Body parameters
  - Outfit size
- A React-based frontend could easily replace this, but currently the focus was on backend.

### Backend
- Contains the Unreal scene used for fitting and rendering.
- Includes a `BackendManager` actor responsible for:
  - Reading input JSON
  - Applying fit configuration
- Scene capture and image output are architecturally planned, but automated execution is currently blocked by MetaHuman API constraints.

> Note: The architecture was intentionally kept simple to focus on validating the fitting and rendering pipeline.

---

## What I would do first at Kloth.me
Based on this exploration:

- I would **not build everything from scratch** — many relevant algorithms already exist.
- I would study and extend **auto-rigging algorithms**, specifically adapting them for clothing meshes.
  - If both body and fabric share a reliable skeletal rig, the first approach becomes much stronger.
- I would study Unreal’s **cloth refitting and auto-resize algorithms** in detail.
  - These are highly relevant to Kloth’s use case.
  - With appropriate APIs, they could be adapted or reimplemented.
- I would explore combining both approaches:
  - Auto-rigging to establish cloth-to-body correspondence
  - Unreal-style refitting to improve accuracy and stability

This hybrid approach could offer both **automation** and **high-quality results**.

---

## Conclusion

- Collision alone is insufficient for virtual try-on
- Rigging provides essential contextual awareness
- MetaHuman offers excellent fitting quality but is not automation-friendly
- A production-ready solution will require a **custom body + cloth pipeline**, inspired by MetaHuman but designed for programmatic control




