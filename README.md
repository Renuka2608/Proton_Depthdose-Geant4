# Proton_Depthdose-Geant4
GEANT4 simulation of proton depth–dose distribution and Bragg peak behavior in a water phantom, with Step-level energy deposition scoring along the beam axis and dose profile analysis.
<br>
The simulation focuses on:

1.Geometry design and material definition (water phantom)

2.Physics list selection for hadronic and electromagnetic interactions

3.Step-level energy deposition scoring along the beam axis 

4.Statistical analysis of dose profiles

The objective is to develop foundational understanding of particle transport and energy deposition mechanisms relevant to proton beam applications.


## Software Architecture

- **DetectorConstruction** — Defines a 20×20×30 cm water phantom inside a 
  1m³ air world. The phantom is the scoring volume.
- **PrimaryGeneratorAction** — Configures the proton beam (energy, direction, 
  position).
- **SteppingAction** — Intercepts every simulation step inside the phantom and 
  records depth (z) and energy deposition, forwarding data to RunAction.
- **EventAction** — Accumulates total energy deposition per event and forwards 
  to RunAction for dose calculation.
- **RunAction** — Uses Geant4's built-in `G4AnalysisManager` to fill a 1D 
  histogram (depth vs energy deposit) and an Ntuple (raw step data), saved 
  as `braggPeak.root`. Handles multi-threading safely via Ntuple merging.

---
## Results
The simulation reproduces the characteristic Bragg peak — low energy deposition 
at shallow depths rising sharply to a maximum before the protons stop at ~150mm.

- **Peak depth:** ~150 mm
- **Total dose in phantom:** ~19 nanoGy (10,000 events)
- **Statistical uncertainty (RMS):** ~24 picoGy

---


## References
- [Geant4 Documentation](https://geant4.web.cern.ch)
- [QBBC Physics List](https://geant4-userdoc.web.cern.ch)