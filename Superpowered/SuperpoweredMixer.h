#ifndef Header_SuperpoweredMixer
#define Header_SuperpoweredMixer

struct stereoMixerInternals;
struct monoMixerInternals;

/**
 @brief Mixer, splitter and Apple 8.24 format converter.
 
 Mixes max. 4 interleaved stereo inputs together. Output can be interleaved or non-interleaved (split). Separate input channel levels (good for gain and pan), separate output channel levels (master gain and pan). Returns maximum values for metering.
 
 One instance allocates just a few bytes of memory.
 */
class SuperpoweredStereoMixer {
public:
/**
 @brief Creates a stereo mixer instance.
 */
    SuperpoweredStereoMixer();
    ~SuperpoweredStereoMixer();
    
/**
 @brief Processes the audio.
 
 @param inputs Four pointers to stereo interleaved input buffers. Any pointer can be NULL.
 @param outputs If outputs[1] is NULL, output is interleaved stereo in outputs[0]. If outputs[1] is not NULL, output is non-interleaved (left side in outputs[0], right side in outputs[1]).
 @param inputLevels Input volume level for each channel. Value changes between consecutive processes are automatically smoothed.
 @param outputLevels Output levels [left, right]. Value changes between consecutive processes are automatically smoothed.
 @param inputMeters Returns with the maximum values for metering. Can be NULL.
 @param outputMeters Returns with the maximum values for metering. Can be NULL.
 @param numberOfSamples The number of samples to process. Minimum 2, maximum 2048.
 @param convertToApple824 If true, outputs in Apple 8.24 format. If false, 32-bit float.
 */
    void process(float *inputs[4], void *outputs[2], float inputLevels[8], float outputLevels[2], float inputMeters[8], float outputMeters[2], unsigned int numberOfSamples, bool convertToApple824);
    
/**
 @brief Converts a stereo interleaved 32-bit float input to stereo interleaved 16-bit signed integer output.
 
 This is a static method, you don't need to create a SuperpoweredStereoMixer instance to use it.
 
 @param input Stereo interleaved 32-bit input. Should be numberOfSamples * 2 + 16 big minimum.
 @param output Stereo interleaved 16-bit output. Should be numberOfSamples * 2 + 16 big minimum.
 @param numberOfSamples The number of samples to process. Should be 4 minimum.
 */
    static void floatToShortInt(float *input, short int *output, unsigned int numberOfSamples);
/**
 @brief Converts two 32-bit float input channels to stereo interleaved 16-bit signed integer output.
 
 This is a static method, you don't need to create a SuperpoweredStereoMixer instance to use it.
 
 @param inputLeft 32-bit input for the left side. Should be numberOfSamples + 8 big minimum.
 @param inputRight 32-bit input for the right side. Should be numberOfSamples + 8 big minimum.
 @param output Stereo interleaved 16-bit output. Should be numberOfSamples * 2 + 16 big minimum.
 @param numberOfSamples The number of samples to process. Should be 4 minimum.
 */
    static void floatToShortInt(float *inputLeft, float *inputRight, short int *output, unsigned int numberOfSamples);
/**
 @brief Converts a stereo interleaved 16-bit signed integer input to stereo interleaved 32-bit float output.
     
 This is a static method, you don't need to create a SuperpoweredStereoMixer instance to use it.
     
 @param input Stereo interleaved 16-bit input. Should be numberOfSamples + 8 big minimum.
 @param output Stereo interleaved 32-bit output. Should be numberOfSamples + 8 big minimum.
 @param numberOfSamples The number of samples to process. Should be 4 minimum.
*/
    static void shortIntToFloat(short int *input, float *output, unsigned int numberOfSamples);
    
private:
    stereoMixerInternals *internals;
    SuperpoweredStereoMixer(const SuperpoweredStereoMixer&);
    SuperpoweredStereoMixer& operator=(const SuperpoweredStereoMixer&);
};

/**
@brief Mixes max. 4 mono inputs into a mono output, with optional conversion to Apple 8.24 format.
 
 One instance allocates just a few bytes of memory.
 */
class SuperpoweredMonoMixer {
public:
/**
 @brief Creates a mono mixer instance.
*/
    SuperpoweredMonoMixer();
    ~SuperpoweredMonoMixer();
    
/**
 @brief Processes the audio.
 
 @param inputs Four pointers to input buffers. Any pointer can be NULL.
 @param output Output buffer.
 @param inputLevels Four input volume levels. Value changes between consecutive processes are automatically smoothed.
 @param outputGain Output level. Value changes between consecutive processes are automatically smoothed.
 @param numberOfSamples The number of samples to process. Minimum 8, maximum 2048, must be exactly divisible with 4.
 @param convertToApple824 If true, outputs in Apple 8.24 format. If false, 32-bit float.
 */
    void process(float **inputs, void *output, float *inputLevels, float outputGain, unsigned int numberOfSamples, bool convertToApple824);
    
private:
    monoMixerInternals *internals;
    SuperpoweredMonoMixer(const SuperpoweredMonoMixer&);
    SuperpoweredMonoMixer& operator=(const SuperpoweredMonoMixer&);
};

#endif
