var element, tuner, imgdata, context;
var note_sharp = ["F#","G","G#","A","A#","B","C","C#","D","D#","E","F"];
var note_flat = ["Gb","G","Ab","A","Bb","B","C","Db","D","Eb","E","F"];
var octave = ["0","1","2","3","4","5"," "];

function create_tuner()
{
    tuner = new Object();
    // layout constants
    tuner.led_spacing = 7;
    tuner.led_width = 3;
    tuner.led_y0 = 5;
    tuner.led_height = 5;
    tuner.pad = 4;
    tuner.tri_y0 = 25;
    // display timing constants
    tuner.speed = 0.15;
    tuner.timestep = 50;
    tuner.in_limit_timestep = 8;
    // other constants
    tuner.scale_lim = 0.03;

    // settable
    tuner.reference_pitch = 440.0;
    tuner.display_flat = false;
    tuner.streaming = true;
    tuner.n_targets = 0;
    tuner.stop = 1;

    // state
    tuner.freq = 0.0;
    tuner.pos = 0.0;
    tuner.in_limit = false;
    tuner.indicate_oc = 0;
    tuner.vis = 0;
    tuner.scale_val = 0.0;
    tuner.note = note_sharp;
    tuner.last_freq = 0.0;
    tuner.freqpoll_id = 0;
    tuner.in_limit_id = 0;
    tuner.timestep_id = 0;
    tuner.target_oc = 0;
    tuner.target_note = 0;
    tuner.strng = 0;
    // caculated layout
    tuner.led_count = 0;
    tuner.width = 0;
    tuner.padding = 0;
    tuner.scale = 0.0;
}

function prepareCanvas(element) {
    window.element = element;
    element.width = document.body.offsetWidth;
 
    if (!element.getContext) {
	return false;
    }
    context = element.getContext('2d');
    //
    configure(element.width);
    rack_tuner_paint(tuner, context, true);
    imgdata = context.getImageData(0, 0, element.width, element.height);
    return true;
}

function drawCanvas(element)
{
    if (prepareCanvas(element)) {
	tuner.stop = 0;
	rack_tuner_freq_poll_handler();
    }
}

function configure(width)
{
    if (width > 400) {
	tuner.scale = 3.0;
    } else {
	tuner.scale = 2.0;
    }
    element.height = tuner.scale * 50;
    context.scale(tuner.scale, tuner.scale);
    var swidth = width / tuner.scale;
    tuner.led_count = (Math.round(1 + (swidth - 2 * tuner.pad - tuner.led_width) / tuner.led_spacing) / 4) * 4;
    tuner.width = (tuner.led_count-1) * tuner.led_spacing + tuner.led_width;
    tuner.padding = (swidth - tuner.width) / 2;
    if (tuner.streaming && tuner.in_limit && !tuner.in_limit_id) {
	tuner.pos = tuner.led_count/2-2;
    }
    tuner.step = tuner.speed * tuner.timestep;
    var step_lim = tuner.led_count/8;
    if (tuner.step > step_lim) {
	tuner.step = step_lim;
    }
}
function rack_tuner_triangle(ctx, posx, posy, width, height)
{
    var h2 = height/2.0;
    ctx.beginPath();
    ctx.moveTo(posx, posy-h2);
    if (width > 0) {
        ctx.bezierCurveTo(posx, posy-h2, posx+10, posy, posx, posy+h2);
    } else {
        ctx.bezierCurveTo(posx, posy-h2, posx-10, posy, posx, posy+h2);
    }
    ctx.bezierCurveTo(posx, posy+h2, posx+width/2, posy+h2, posx+width, posy);
    ctx.bezierCurveTo(posx+width, posy, posx+width/2, posy-h2, posx, posy-h2);
    ctx.fill();
}
function rgb(r, g, b)
{
    return "rgb("+Math.round(r*255)+","+Math.round(g*255)+","+Math.round(b*255)+")";
}
function rgba(r, g, b, a)
{
    return "rgba("+Math.round(r*255)+","+Math.round(g*255)+","+Math.round(b*255)+","+a+")";
}
function rack_tuner_display_note(ctx, center, y0, indicate_oc, vis, scale)
{
    var pitch_add = Math.abs(tuner.reference_pitch - 440.00);
    ctx.fillStyle = rgba(Math.abs(scale)+(pitch_add*0.1), 1-(scale*scale+(pitch_add*0.1)), 0.2, 1-Math.abs(scale));
    ctx.font = "12px sans-serif";
    var sharp_width = ctx.measureText("#").width;
    ctx.font = "18px sans-serif";
    var g_step = ctx.measureText("G").width;
    var x0 = center - (g_step + sharp_width)/2 + 1;
    nt = tuner.note[vis];
    ctx.textBaseline = "middle";
    ctx.textAlign = "left";
    ctx.fillText(nt[0], x0, y0);
    x0 += g_step;
    if (nt.length > 1) {
	ctx.font = "12px sans-serif";
	ctx.textBaseline = "bottom";
	ctx.fillText(nt[1], x0, y0+2);
    }
    ctx.font = "9px sans-serif";
    ctx.textBaseline = "top";
    ctx.fillText(octave[indicate_oc], x0, y0);
}
function rack_tuner_paint(tuner, ctx, paint_bg)
{
    ctx.lineWidth = 1;
    var center = tuner.padding + tuner.width/2;
    var dist = 20;
    var tri0 = center-15-dist;
    var tri1 = center+15+dist;
    if (paint_bg) {
	ctx.fillStyle = rgb(0.3,0.3,0.3);
	for (var i = 0; i < tuner.led_count; i++) {
	    ctx.fillRect(tuner.padding+i*tuner.led_spacing, tuner.led_y0, tuner.led_width, tuner.led_height);
	}
	rack_tuner_triangle(ctx, tri0, 25, 15, 10);
	rack_tuner_triangle(ctx, tri1, 25, -15, 10);
	return;
    }
    ctx.putImageData(imgdata, 0, 0);
    if (tuner.freq == 0.0) {
	return;
    }
    if (tuner.streaming) {
	var pat = ctx.createLinearGradient(0, 0, tuner.width, 0);
	pat.addColorStop(1, rgb(1, 0.1, 0.1));
	pat.addColorStop(0.65, rgb(0.8, 0.8, 0.1));
	pat.addColorStop(0.5, rgb(0.1, 0.8, 0.1));
	pat.addColorStop(0.35, rgb(0.8, 0.8, 0.1));
	pat.addColorStop(0, rgb(1, 0.1, 0.1));
        ctx.fillStyle = pat;
	if (tuner.in_limit) {
	    ctx.fillStyle = rgb(0, 1, 0);
	    var n = tuner.led_count/2-tuner.pos;
	    if (n > 4) {
		n = 4;
	    }
	    for (var i = 0; i < n; i++) {
		ctx.fillRect(tuner.padding+(tuner.pos+i)*tuner.led_spacing, tuner.led_y0, tuner.led_width, tuner.led_height);
		ctx.fillRect(tuner.padding+(tuner.led_count-1-i-tuner.pos)*tuner.led_spacing, tuner.led_y0, tuner.led_width, tuner.led_height);
	    }
            
	} else {
	    // led display: 2 .. tuner.led_count/8+1
	    var lim = 1+Math.floor(1+(Math.abs(tuner.scale_val)-tuner.scale_lim)*tuner.led_count/4.0);
	    ctx.fillStyle = rgb(1, 0, 0); // comment out for gradient
	    if (Math.abs(tuner.scale_val) >= tuner.scale_lim) {
		for (var i = 0; i < tuner.led_count; i++) {
		    var j = Math.floor(tuner.led_count+i-tuner.pos) % (tuner.led_count/2);
		    if (j < 0) {
			j = -j;
		    }
		    if (lim <= j) {
			continue;
		    }
		    ctx.fillRect(tuner.padding+i*tuner.led_spacing, tuner.led_y0, tuner.led_width, tuner.led_height);
		}
	    }
	}
    } else {
	var s = 0.5+tuner.scale_val;
	if (s < 0) {
	    s = 0;
	} else if (s > 1) {
	    s = 1;
	}
	var sz = 2 * tuner.width * tuner.scale_lim;
	ctx.fillStyle = rgb(1, 0, 0);
	ctx.fillRect(tuner.padding+s*(tuner.width-sz), tuner.led_y0, sz, tuner.led_height);
	if (Math.abs(tuner.scale_val) < 0.4) {
	    ctx.fillStyle = rgb(cr,1, 1, 0);
	    ctx.fillRect(tuner.padding+0.5*(tuner.width-tuner.led_width), tuner.led_y0, tuner.led_width, tuner.led_height);
	}
    }
    if (tuner.scale_val < tuner.scale_lim) {
	ctx.fillStyle = rgb(0.80,0.79,0.01);
	rack_tuner_triangle(ctx, tri0, tuner.tri_y0, 15, 10);
    }
    if (tuner.scale_val > -tuner.scale_lim) {
	ctx.fillStyle = rgb(0.80,0.79,0.01);
	rack_tuner_triangle(ctx, tri1, tuner.tri_y0, -15, 10);
    }
    rack_tuner_display_note(ctx, center, tuner.tri_y0, tuner.indicate_oc, tuner.vis, tuner.scale_val);
/*
    if (tuner.n_targets > 0) {
	cairo_set_font_size(cr,12.0);
	char sd[10];
	int n = snprintf(sd, sizeof(sd), "%d: %s", tuner->strng, tuner->note[tuner->target_note]);
	char c = sd[n-1];
	if (c == '#' || c == 'b') {
	    sd[n-1] = 0;
	    n -= 1;
	}
	cairo_text_extents_t ex;
	cairo_text_extents(cr, sd, &ex);
	sd[n] = '#';
	sd[n+1] = 0;
	cairo_text_extents(cr, sd, &ex);
	cairo_move_to(cr,tuner.pad + (tri0-tuner.pad) / 2 - ex.width/2, tuner.tri_y0 - ex.y_bearing/2);
	cairo_set_source_rgb(cr,0.95,0.95,0.3);
	sd[n] = 0;
	cairo_show_text(cr, sd);
	double pt_x, pt_y;
	cairo_get_current_point(cr, &pt_x, &pt_y);
	cairo_set_font_size(cr,9.0);
	cairo_rel_move_to(cr,0,-ex.y_bearing/2);
	cairo_show_text(cr, octave[tuner->target_oc]);
	if (c == '#' || c == 'b') {
	    cairo_move_to(cr,pt_x, tuner.tri_y0);
	    sd[0] = c;
	    sd[1] = 0;
	    cairo_show_text(cr, sd);
	}
    }
*/
    // display frequency
    ctx.fillStyle = rgba(0.8, 0.8, 0.2,0.6);
    ctx.font = "7px sans-serif";
    ctx.textBaseline = "bottom";
    ctx.textAlign = "right"
    ctx.fillText(tuner.freq.toFixed(1) + " Hz", tuner.width, tuner.tri_y0);
}
function rack_tuner_pitch_to_note(fnote, ret)
{
    ret.note = Math.round(fnote);
    ret.scale = fnote - ret.note;
    ret.oc = Math.round(ret.note/12);
    if (ret.oc < 0 || ret.oc >= octave.length) {
	ret.oc = octave.length - 1;
    }
    ret.note = ret.note % 12;
    if (ret.note < 0) {
	ret.note += 12;
    }
}
function log2(v)
{
    return Math.log(v) / Math.log(2);
}
function rack_tuner_calc()
{
    var fvis = 12 * (log2(tuner.freq/tuner.reference_pitch) + 4) + 3;
    var ret = {};
    rack_tuner_pitch_to_note(fvis, ret);
    tuner.indicate_oc = ret.oc;
    tuner.vis = ret.note;
    tuner.scale_val = ret.scale;
    if (tuner.n_targets === 0) {
	return;
    }
    var m0 = 1e10;
    var i0 = 0;
    for (var i = 0; i < tuner.n_targets; i++) {
	var t = Math.abs(fvis-tuner.targets[i]);
	if (t < m0) {
	    m0 = t;
	    i0 = i;
	}
        tuner.strng = tuner.n_targets - i0;
        var val = tuner.targets[i0];
	rack_tuner_pitch_to_note(val, ret);
	tuner.target_oc = ret.oc;
	tuner.target_note = ret.note;
	tuner.scale_val = fvis - val;
	if (tuner.scale_val > 0.5) {
	    tuner.scale_val = 0.5;
	} else if (tuner.scale_val < -0.5) {
	    tuner.scale_val = -0.5;
	}
    }
}
function rack_tuner_freq_poll_handler()
{
//
    if (element.width != document.body.offsetWidth) {
	element.width = document.body.offsetWidth;
	configure(element.width);
	window.scrollTo(0, 1);
	rack_tuner_paint(tuner, context, true);
	imgdata = context.getImageData(0, 0, element.width, element.height);
    }
//
    var timestep = tuner.timestep;
    if (tuner.freq != tuner.last_freq) {
	tuner.last_freq = tuner.freq;
	if (tuner.freq == 0.0) {
	    rack_tuner_paint(tuner, context, false);
	    setTimeout(rack_tuner_freq_poll_handler, timestep);
	    return;
	}
	rack_tuner_calc(tuner);
    } else {
	if (tuner.freq == 0.0 || Math.abs(tuner.scale_val) < tuner.scale_lim) {
	    setTimeout(rack_tuner_freq_poll_handler, timestep);
	    return;
	}
    }
    if (tuner.streaming) {
	if (Math.abs(tuner.scale_val) >= tuner.scale_lim) {
	    tuner.in_limit = false;
	    var skip;
	    if (tuner.scale_val > 0) {
		skip = 1;
		timestep = tuner.timestep / (tuner.step * tuner.scale_val);
	    } else if (tuner.scale_val < 0) {
		skip = -1;
		timestep = tuner.timestep / (tuner.step * -tuner.scale_val);
	    }
	    while (timestep < tuner.timestep) {
		timestep *= 2;
		skip *= 2;
	    }
	    while (timestep > 2 * tuner.timestep) {
		timestep /= 2;
		skip /= 2;
	    }
	    tuner.pos += skip;
	    if (tuner.pos >= tuner.led_count) {
		tuner.pos = 0.0;
	    } else if (tuner.pos < 0) {
		tuner.pos = tuner.led_count-1;
	    }
	} else if (!tuner.in_limit) {
	    tuner.in_limit = true;
	    tuner.pos = 0;
	    if (!tuner.in_limit_id) {
		tuner.in_limit_id = setInterval(rack_tuner_show_in_limit, tuner.in_limit_timestep);
	    }
	}
    }
    rack_tuner_paint(tuner, context, false);
    if (!tuner.stop) {
	setTimeout(rack_tuner_freq_poll_handler, timestep);
    }
}
function rack_tuner_show_in_limit()
{
    if (!tuner.in_limit || tuner.pos >= tuner.led_count/2-2) {
	clearInterval(tuner.in_limit_id);
	tuner.in_limit_id = 0;
	return;
    }
    tuner.pos += 1;
    rack_tuner_paint(tuner, context, false);
}
