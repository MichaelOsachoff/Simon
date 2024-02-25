# Simon
An implementation of the retro Simon game on Adafruit Circuit Playground Express

## Implementation
### General
Sounds are generated through the onboard speaker. The main gameplay loop notes were based off of the majority of the retro Simon games post 1978, which used an A major triad to ensure the sequences of notes would be harmonic.

The happy notes were set to an augmented a major in the same octaves to maintain a similar sound but play at notably different rates to indicate the player has won.

The unhappy notes use the B flat in the second octave as by ear it sounded close to the sounds a player would hear when failing the original game.

Current implementation does not contain lights, must be played solely by ear, and the player must play **5 notes correctly**.

### Gameplay notes
E3, A3, C4#, E4

### Happy (Win) notes
E3#, A3, C4#, E4#

### Unhappy (Fail) notes
B2♭

## Resources used
[Retro Simon Game](https://en.wikipedia.org/wiki/Simon_(game))

[A major chord table](https://en.wikipedia.org/wiki/Major_chord#Major_chord_table)

[Augmented A major chord table](https://en.wikipedia.org/wiki/Augmented_triad#Augmented_chord_table)
