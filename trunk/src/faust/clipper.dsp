declare id "clipper";
declare name "Clip";
declare category "Fuzz";
declare samplerate "96000";

asymclip = ffunction(float asymclip(float), "clipping.h", "");
asclip = asymclip(_);

asymclip2 = ffunction(float asymclip2(float), "clipping.h", "");
asclip2 = asymclip2(_);

asymclip3 = ffunction(float asymclip3(float), "clipping.h", "");
asclip3 = asymclip3(_);

asymclip4 = ffunction(float asymclip4(float), "clipping.h", "");
asclip4 = asymclip4(_);

asymhardclip = ffunction(float asymhardclip(float), "clipping.h", "");
ashardclip = asymhardclip(_);


asymhardclip2 = ffunction(float asymhardclip2(float), "clipping.h", "");
ashardclip2 = asymhardclip2(_);

symclip = ffunction(float symclip(float), "clipping.h", "");
sclip = symclip(_);

symclip2 = ffunction(float symclip2(float), "clipping.h", "");
sclip2 = symclip2(_);

process = asclip4;
