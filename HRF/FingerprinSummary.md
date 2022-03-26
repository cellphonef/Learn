# Fingerprint Summary

For fingerprint we have two important task:
- Verification (1-1 Matching)
- Classification (1-N Matching)

In a Automatic Fingerprint Recognition System (AFRS), We ues query to matching template store in database.

## Fingerprint Representation & Feature Extraction 

> Q: How to represent fingerprint for verification or classification?

### Fingerprint Feature

There are three level features in fingerprint:
- Level One: Global Level, overall ridge flow pattern
  - Sigular point
    - Arch
    - Whorl
    - Loop 
- Level Two: Local Level, minutiae points
  - ridge bifucation
  - ridge ending
- Level Three: Very-Fine Level (800-1000dpi required)
  - Sweat Pore
  - Ridge contours


### Minutiae-based representation

**Representation**

Minutiae-based representation is a feature vector (of variable length, unordered) whose elements are the fingerprint minutiae. Each minutia is described by a number of attributes, including its location in the fingerprint image, orientation, type (e.g., ridge ending or ridge bifurcation), a weight based on the quality of the fingerprint image in the neighborhood of the minutia, and so on.

Most common minutiae-based representation consider each minutia as a triplet **m** = {x, y, θ} that indicates the x, y minutia location coordinates and the minutia angel θ.

So, Using minutiae-based representation, a fingerprint 
$$F = \{m_1, m_2, ..., m_m\},  m_i = \{x_i, y_i, θ_i \},  i=1..m$$
where m denote the number of minutiae of fingerprint.

**Shortage**

Minutiae-based representations have shortages:
- Minutiae-based representations are of variable length and unordered, since the number of extraced minutiae varies amongst different fingerprint images even of the same finger. Variations in the number of minutiae originate from a user's interaction with the fingerprint reader (placement position and applied pressure) and condition of the finger (dry, wet, cuts, bruises, etc.).
- Reliable minutiae extraction in low quality fingerprints (due to noise, distortion, finger condition) is problematic, causing false rejects.

In the context of global population registration.


This necessitates extremely discriminative yet compact representations that are complementary and at least as discriminative as the traditional minutiae-based representation.

### Pore-based representation

Pore-based representation is a feature vector whose elements are the fingerprint pore patch embbeding. 



### Fixed-Length representation







## Fingerprint Matcing & Recognition

### Minutiae-Based Matching





1. Localize the minutiae point and extract
2. Find minutiae point correspondences
3. Calculate similiarity
4. Use threshold to do decision 


### Pore-Base Matching





## Evaluation

- False Matching Rate (FMR)
  - FMR100
  - FMR1000
- False Non-Matching Rate (FNMR)
- Equal Error Rate (EER)
- Receiver of Curve (ROC)
- Detect Error Trade-off
- False Acceptance Rate (FAR)
- False Rejection Rate (FRR)



## Open Problem


## Public dataset

- PolyU HRF
- FVC(2002, 2004)
- FVC
- NIST fingerprint databases
- SPD2010


### PolyU HRF


