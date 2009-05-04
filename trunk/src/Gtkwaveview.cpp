// ***** GtkWaveView.cpp *****
/******************************************************************************
part of guitarix, show a wave with Gtk
******************************************************************************/

//#include"./guitarix/Gtkwaveview.h"

#define GTK_TYPE_WAVEVIEW          (gtk_waveview_get_type())
#define GTK_WAVEVIEW(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_WAVEVIEW, GtkWaveView))
#define GTK_IS_WAVEVIEW(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_WAVEVIEW))
#define GTK_WAVEVIEW_CLASS(klass)  (G_TYPE_CHECK_CLASS_CAST ((klass),  GTK_TYPE_WAVEVIEW, GtkWaveViewClass))
#define GTK_IS_WAVEVIEW_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GTK_TYPE_WAVEVIEW))

GtkWaveView::GtkWaveView()
// GtkWaveView constructor
{

}

GtkWaveView::~GtkWaveView()
{
    // Nothing specific to do...
}

struct GtkWaveViewClass
{
    GtkRangeClass parent_class;
    GdkPixbuf *waveview_image;
    GdkPixbuf *bigwaveview_image;
    GdkPixbuf *liveview_image;
    GdkPixbuf *livecontrol_image;
    GtkTooltips *comandline;

    int waveview_x;
    int waveview_y;
    int waveleft;
    int wavestay;
    int wavebutton;
    const char* fileview;

    int offset_cut;
    int length_cut;
    int filelength;
    double  drawscale;

    int liveview_x;
    int liveview_y;
    int livecontrol_x;
    int livecontrol_y;
    float *live_view;
    float *live_viewin;
    // float *live_freq;
    int new_pig;
    int mode;
    int speed;
    float *wave_save;
    int ringis;
};

GType gtk_waveview_get_type ();

int new_wave;
//int view_mode = 0;

SNDFILE *soundin_openview(const char* name, int *chans, float *sr, int *length)
{
    SF_INFO info;
    SNDFILE *sf = sf_open(name, SFM_READ, &info);
    *sr     = (float) info.samplerate;
    *chans  =   info.channels;
    *length =   (int)   info.frames;
    return sf;
}

int sounddrawview(SNDFILE *pInput, float *buffer, int vecsize)
{
    return (int) sf_readf_float(pInput, buffer, vecsize);
}

static gboolean gtk_waveview_expose (GtkWidget *widget, GdkEventExpose *event)
{
    g_assert(GTK_IS_WAVEVIEW(widget));
    GtkWaveView *waveview = GTK_WAVEVIEW(widget);

    if (    waveview->waveview_type == 0)
    {
        int waveviewx = widget->allocation.x, waveviewy = widget->allocation.y;
        waveviewx += (widget->allocation.width - GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->waveview_x) *0.5;
        waveviewy += (widget->allocation.height - GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->waveview_y) *0.5;
        if (new_wave != 0)
        {
            new_wave = 0;
            GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->fileview = jconvwav.c_str();
            GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->offset_cut = 0;
            GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->length_cut = 0;

            SNDFILE *pvInput;
            int counter=0,chans,vecsize=64, length=0,length2=0, countfloat, countframe = 1;
            float *sig,sr;
            GdkGC * line = gdk_gc_new(GDK_DRAWABLE(widget->window));
            GdkColor color ;
            color.red = 30 * 236;
            color.blue = 30 * 236;
            color.green = 30 * 236;
            gdk_gc_set_rgb_fg_color(line, &color);
            gdk_gc_set_line_attributes (line, 1,GDK_LINE_SOLID,GDK_CAP_BUTT,GDK_JOIN_MITER);
            gdk_draw_rectangle(GDK_DRAWABLE(widget->window), line,TRUE, 0, 0,300,200);
            color.red = 20 * 256;
            color.blue =20 * 256;
            color.green = 200 * 256;
            gdk_gc_set_rgb_fg_color(line, &color);
            gdk_draw_line(GDK_DRAWABLE(widget->window), line, 0, 100,300,100);
            color.red = 200 * 256;
            color.blue =200 * 256;
            color.green = 200 * 256;
            gdk_gc_set_rgb_fg_color(line, &color);

            if (!(pvInput=soundin_openview(GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->fileview, &chans, &sr, &length2)))
            {
                color.red = 200 * 236;
                color.blue = 30 * 236;
                color.green = 30 * 236;
                gdk_gc_set_rgb_fg_color(line, &color);
                gdk_gc_set_line_attributes (line, 8,GDK_LINE_SOLID,GDK_CAP_BUTT,GDK_JOIN_MITER);
                gdk_draw_line(GDK_DRAWABLE(widget->window), line, 0, 0,300,200);
                gdk_draw_line(GDK_DRAWABLE(widget->window), line, 300, 0,0,200);
                gdk_gc_set_line_attributes (line, 1,GDK_LINE_SOLID,GDK_CAP_BUTT,GDK_JOIN_MITER);
                color.red = 200 * 256;
                color.blue =200 * 256;
                color.green = 200 * 256;
                gdk_gc_set_rgb_fg_color(line, &color);
                GdkColormap*  col =      gdk_colormap_get_system ();
                gdk_pixbuf_get_from_drawable( GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->waveview_image,GDK_DRAWABLE(widget->window), col,0,0,0,0,300,200);
                sf_close(pvInput);
            }
            else
            {
                sig      = new float[vecsize*2];
                GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->drawscale = 300.0/length2;
                GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->filelength = length2;
                if (chans == 1)
                {
                    while (counter<length+length2-1)
                    {
                        sounddrawview(pvInput, sig,vecsize);
                        counter=counter+64;
                        countfloat = 0;
                        while (countfloat<vecsize*chans)
                        {
                            gdk_draw_line(GDK_DRAWABLE(widget->window), line, countframe*GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->drawscale, 100,countframe*GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->drawscale,sig[countfloat]*100.0+100);
                            countfloat +=1;
                            countframe +=1;
                        }
                    }
                    GdkColormap*  col =      gdk_colormap_get_system ();
                    gdk_pixbuf_get_from_drawable( GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->waveview_image,GDK_DRAWABLE(widget->window), col,0,0,0,0,300,200);
                    sf_close(pvInput);
                    delete[] sig;
                }
                else if  (chans == 2)
                {
                    color.red = 20 * 256;
                    color.blue =20 * 256;
                    color.green = 200 * 256;
                    gdk_gc_set_rgb_fg_color(line, &color);
                    gdk_draw_line(GDK_DRAWABLE(widget->window), line, 0, 150,300,150);
                    gdk_draw_line(GDK_DRAWABLE(widget->window), line, 0, 50,300,50);
                    color.red = 200 * 256;
                    color.blue =200 * 256;
                    color.green = 200 * 256;
                    gdk_gc_set_rgb_fg_color(line, &color);
                    int tingeltangel = 0;
                    while (counter<length+length2-1)
                    {
                        sounddrawview(pvInput, sig,vecsize);
                        counter=counter+64;
                        countfloat = 0;
                        while (countfloat<vecsize*chans)
                        {
                            if  ( tingeltangel == 0)
                            {
                                gdk_draw_line(GDK_DRAWABLE(widget->window), line, countframe*GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->drawscale, 50,countframe*GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->drawscale,sig[countfloat]*50.0+50);
                                tingeltangel = 1;
                            }
                            else if  ( tingeltangel == 1)
                            {
                                gdk_draw_line(GDK_DRAWABLE(widget->window), line, countframe*GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->drawscale, 150,countframe*GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->drawscale,sig[countfloat]*50.0+150);
                                tingeltangel = 0;
                            }
                            countfloat +=1;
                            countframe +=1;
                        }
                    }
                    GdkColormap*  col =      gdk_colormap_get_system ();
                    gdk_pixbuf_get_from_drawable( GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->waveview_image,GDK_DRAWABLE(widget->window), col,0,0,0,0,300,200);
                    sf_close(pvInput);
                    delete[] sig;
                }
            }
            g_object_unref(line );

            if ((offcut != GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->offset_cut) || (lenghtcut != GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->length_cut))
            {
                GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->offset_cut = offcut;
                GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->length_cut = lenghtcut;
                GdkGC * line = gdk_gc_new(GDK_DRAWABLE(widget->window));
                GdkColor color ;
                gdk_gc_set_function(line, GDK_OR);
                color.red = 50 * 236;
                color.blue = 50 * 236;
                color.green = 70 * 236;
                gdk_gc_set_rgb_fg_color(line, &color);
                gdk_gc_set_line_attributes (line, 1,GDK_LINE_SOLID,GDK_CAP_BUTT,GDK_JOIN_MITER);
                gdk_draw_rectangle(GDK_DRAWABLE(widget->window), line,TRUE, offcut*GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->drawscale, 0,lenghtcut*GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->drawscale,200);
                GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wavestay = offcut*GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->drawscale;
                GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->waveleft = lenghtcut*GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->drawscale;
                g_object_unref(line );
            }
            gdk_pixbuf_get_from_drawable( GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigwaveview_image,GDK_DRAWABLE(widget->window), gdk_colormap_get_system (),0,0,0,0,300,200);
        }
        gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigwaveview_image, 0,0, 0, 0, 300, 200, GDK_RGB_DITHER_NORMAL, 0, 0);
    }

    else if (    waveview->waveview_type == 1)
    {

        int liveviewx = widget->allocation.x, liveviewy = widget->allocation.y;
        liveviewx += (widget->allocation.width - GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->liveview_x) *0.5+15;
        liveviewy += (widget->allocation.height - GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->liveview_y) *0.5+15;
        int scaletype = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->mode;
        view_mode = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->mode;
        cairo_t *     cr =       gdk_cairo_create(GDK_DRAWABLE(widget->window));
        if (GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->new_pig == 0)
        {
            cairo_pattern_t *pat;
            pat = cairo_pattern_create_radial (-130.4, -270.4, 1.6, -1.4,  -4.4, 300.0);
            cairo_pattern_add_color_stop_rgba (pat, 0, 0.2, 0.2, 0.3, 1);
            cairo_pattern_add_color_stop_rgba (pat, 1, 0.05, 0.05, 0.05, 1);
            cairo_set_source_rgb(cr, 0.05, 0.05, 0.05);
            cairo_rectangle (cr, liveviewx-5, liveviewy-5, 460, 60);
            cairo_set_source (cr, pat);
            cairo_fill (cr);
            cairo_pattern_destroy (pat);

            cairo_set_line_width (cr, 10);
            cairo_set_source_rgba (cr, 0, 0, 0,0.4);
            cairo_rectangle (cr, liveviewx-5, liveviewy-5, 460, 60);
            cairo_stroke (cr);
            cairo_set_line_width (cr, 1);
            cairo_set_source_rgba (cr, 0.1, 0.1, 0.1,0.7);
            cairo_rectangle (cr, liveviewx-6, liveviewy-6, 462, 62);
            cairo_stroke (cr);
            cairo_set_line_width (cr, 1);
            cairo_set_source_rgba (cr, 0.5, 0.5, 0.5,0.1);
            cairo_rectangle (cr, liveviewx-12, liveviewy-12, 474, 74);
            cairo_rectangle (cr, liveviewx-2, liveviewy-2, 454, 54);
            cairo_stroke (cr);

            cairo_set_line_width (cr, 1.5);
            cairo_set_source_rgba (cr,0.2, 1.0, 0.2, 0.4);
            cairo_move_to (cr, liveviewx, liveviewy+25);
            cairo_line_to (cr, liveviewx+450, liveviewy+25);
            cairo_stroke (cr);
            cairo_set_source_rgba (cr,0.2, 1.0, 0.2, 0.4);
            cairo_rectangle (cr, liveviewx, liveviewy, 450.0, 50.0);
            cairo_stroke (cr);
            int gitter = 0;
            for (int i=0; i<45; i++)
            {
                gitter += 10;
                cairo_move_to (cr, liveviewx+gitter-5, liveviewy);
                cairo_line_to (cr, liveviewx+gitter-5, liveviewy+50);
            }
            gitter = 0;
            for (int i=0; i<5; i++)
            {
                gitter += 10;
                cairo_move_to (cr, liveviewx, liveviewy+gitter-5);
                cairo_line_to (cr, liveviewx+450, liveviewy+gitter-5);
            }
            cairo_set_source_rgba (cr,0.2,  1.0, 0.2, 0.05);
            cairo_stroke (cr);
            gdk_pixbuf_get_from_drawable( GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->liveview_image,GDK_DRAWABLE(widget->window), gdk_colormap_get_system (),liveviewx-15, liveviewy-15,0,0,480,80);
    //    }  //background pixmap ready
    //    else if (GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->new_pig <= 1)
    //    {

            double x0      = liveviewx+476,
                             y0      = liveviewy-5,
                                       rect_width  = 40.,
                                                     rect_height = 15.;
            double x1,y1;
            for (int i=0; i<3; i++)
            {
                x1=x0+rect_width;
                y1=y0+rect_height;
                cairo_move_to  (cr, x0, (y0 + y1)/2);
                cairo_curve_to (cr, x0 ,y0, x0, y0, (x0 + x1)/2, y0);
                cairo_curve_to (cr, x1, y0, x1, y0, x1, (y0 + y1)/2);
                cairo_curve_to (cr, x1, y1, x1, y1, (x1 + x0)/2, y1);
                cairo_curve_to (cr, x0, y1, x0, y1, x0, (y0 + y1)/2);
                cairo_close_path (cr);
                cairo_set_source_rgba (cr, 0.08, 0.08, 0.09,0.3);
                cairo_fill_preserve (cr);
                cairo_set_source_rgba (cr, 0.01, 0.01, 0.01, 0.3);
                cairo_set_line_width (cr, 3.0);
                cairo_stroke (cr);

                x1=x0+rect_width-2;
                y1=y0+rect_height-2;
                cairo_move_to  (cr, x0+2, (y0+2 + y1)/2);
                cairo_curve_to (cr, x0+2 ,y0+2, x0+2, y0+2, (x0+2 + x1)/2, y0+2);
                cairo_curve_to (cr, x1, y0+2, x1, y0+2, x1, (y0+2 + y1)/2);
                cairo_curve_to (cr, x1, y1, x1, y1, (x1 + x0+2)/2, y1);
                cairo_curve_to (cr, x0+2, y1, x0+2, y1, x0+2, (y0+2 + y1)/2);
                cairo_close_path (cr);
                cairo_move_to  (cr, x0, (y0 + y1)/2);
                cairo_curve_to (cr, x0 ,y0, x0, y0, (x0 + x1)/2, y0);
                cairo_curve_to (cr, x1, y0, x1, y0, x1, (y0 + y1)/2);
                cairo_curve_to (cr, x1, y1, x1, y1, (x1 + x0)/2, y1);
                cairo_curve_to (cr, x0, y1, x0, y1, x0, (y0 + y1)/2);
                cairo_close_path (cr);
                cairo_set_source_rgba (cr, 0.0, 0.0, 0.0, 0.9);
                cairo_set_line_width (cr, 1.5);
                cairo_stroke (cr);
                y0      += 22;
            }
            x0      = liveviewx+470,
                      y0      = liveviewy-10,
                                rect_width  = 49.,
                                              rect_height = 68.;
            x1=x0+rect_width;
            y1=y0+rect_height;
            cairo_move_to  (cr, x0, (y0 + y1)/2);
            cairo_curve_to (cr, x0 ,y0, x0, y0, (x0 + x1)/2, y0);
            cairo_curve_to (cr, x1, y0, x1, y0, x1, (y0 + y1)/2);
            cairo_curve_to (cr, x1, y1, x1, y1, (x1 + x0)/2, y1);
            cairo_curve_to (cr, x0, y1, x0, y1, x0, (y0 + y1)/2);
            cairo_close_path (cr);
            cairo_set_source_rgba (cr, 0.08, 0.08, 0.09,0.2);
            cairo_fill_preserve (cr);
            cairo_set_source_rgba (cr, 0.01, 0.01, 0.01, 0.8);
            cairo_set_line_width (cr, 1.5);
            cairo_stroke (cr);

            GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->new_pig += 1;

            gdk_pixbuf_get_from_drawable( GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->livecontrol_image,GDK_DRAWABLE(widget->window), gdk_colormap_get_system (),liveviewx+470, liveviewy-10,0,0,50,80);
        }  //controll pixmap ready

        gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->liveview_image, 0,0,liveviewx-15, liveviewy-15 , 480, 80, GDK_RGB_DITHER_NORMAL, 0, 0);
        gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->livecontrol_image, 0,0,liveviewx+470, liveviewy-10 , 50, 80, GDK_RGB_DITHER_NORMAL, 0, 0);

        string ti, tfi;
        IntToString( time_is/100000 ,ti);
        string      tir = " ht frames ";
        tir += ti;
        cairo_set_source_rgba (cr, 0.8, 0.8, 0.2,0.6);
        cairo_set_font_size (cr, 7.0);
        cairo_move_to (cr, liveviewx, liveviewy+48);
        cairo_show_text(cr, tir.c_str());
        /*  IntToString(int(GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->live_freq[0]),tfi);
            cairo_move_to (cr, liveviewx, liveviewy+10);
            tir = "freq ";
            tir += tfi;
            cairo_show_text(cr, tir.c_str()); */
        cairo_stroke (cr);

        if (scaletype == 1)
        {

            double x0      = liveviewx+476,
                             y0      = liveviewy-5,
                                       rect_width  = 40.,
                                                     rect_height = 15.;
            double x1,y1;

            x1=x0+rect_width;
            y1=y0+rect_height;
            cairo_move_to  (cr, x0, (y0 + y1)/2);
            cairo_curve_to (cr, x0 ,y0, x0, y0, (x0 + x1)/2, y0);
            cairo_curve_to (cr, x1, y0, x1, y0, x1, (y0 + y1)/2);
            cairo_curve_to (cr, x1, y1, x1, y1, (x1 + x0)/2, y1);
            cairo_curve_to (cr, x0, y1, x0, y1, x0, (y0 + y1)/2);
            cairo_close_path (cr);
            cairo_set_source_rgba (cr, 0.2, 0.8, 0.2,0.2);
            cairo_fill_preserve (cr);
            cairo_set_source_rgba (cr, 0.01, 0.01, 0.01, 0.8);
            cairo_set_line_width (cr, 3.0);
            cairo_stroke (cr);

            float wave_go = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->live_view[0]*500.0;
            float wave_db = log(fabs( wave_go*0.002))*6/log(2);
            double xl = floor(exp(log(1.055)*2.1*wave_db)*285);
            if (xl > 225.0)   xl = 225.0;
            else if (xl < -225.0)   xl = -225.0;
            double redline = 0.2;
            if (wave_go > 75.0)
            {
                redline = 1.0;
                wave_go = 75.0;
            }
            else if (wave_go < -75.0)
            {
                redline = 1.0;
                wave_go = -75.0;
            }

            cairo_set_source_rgba (cr,  redline, 1.0, 0.2,0.8);
            cairo_set_line_width (cr, 1.0);
            cairo_move_to (cr, liveviewx+450, liveviewy+25);
            for (int i=0; i<frag; i++)
            {
               
                cairo_line_to (cr, liveviewx+350-(250.0/frag)-((250.0/frag)*i+1), liveviewy+25+double(get_frame[i])*75.0);
             
            }
            cairo_line_to (cr, liveviewx, liveviewy+25);
	    cairo_pattern_t *linpat;
	    linpat = cairo_pattern_create_linear (450, 0, 450, 42);
	    cairo_pattern_set_extend(linpat, CAIRO_EXTEND_REFLECT);
	    cairo_pattern_add_color_stop_rgba (linpat, 0.4, 1, 0.2, 0,0.8);
	    cairo_pattern_add_color_stop_rgba (linpat, 0.8, 0.2, 1, 0.2,0.8);
	    cairo_set_source (cr, linpat);
            cairo_close_path (cr);
            cairo_fill_preserve (cr);
            cairo_stroke (cr);
            cairo_pattern_destroy (linpat);
 
         /*   cairo_move_to (cr, liveviewx, liveviewy+25);
            cairo_curve_to (cr, liveviewx+75+wave_go,liveviewy+25-wave_go, liveviewx+150+wave_go,liveviewy+25+wave_go, liveviewx+225+wave_go,liveviewy+25);
            cairo_curve_to (cr, liveviewx+300+wave_go,liveviewy+25-wave_go, liveviewx+375+wave_go,liveviewy+25+wave_go, liveviewx+450,liveviewy+25);
            cairo_stroke (cr); */

            double dashes[] = {5.0, 1.0 };
            cairo_set_dash (cr, dashes, 2, -0.25);
            cairo_move_to (cr, liveviewx+225-xl, liveviewy);
            cairo_line_to (cr, liveviewx+225+xl, liveviewy);
            cairo_move_to (cr, liveviewx+225-xl, liveviewy+50);
            cairo_line_to (cr, liveviewx+225+xl, liveviewy+50);
            cairo_set_source_rgba (cr,  redline, 1.0, 0.2,0.8);
            cairo_set_line_width (cr, 3.0);
            cairo_stroke (cr);
            cairo_destroy(cr);
        }

        else if (scaletype == 2)
        {

            double x0      = liveviewx+476,
                             y0      = liveviewy+17,
                                       rect_width  = 40.,
                                                     rect_height = 15.;
            double x1,y1;

            x1=x0+rect_width;
            y1=y0+rect_height;
            cairo_move_to  (cr, x0, (y0 + y1)/2);
            cairo_curve_to (cr, x0 ,y0, x0, y0, (x0 + x1)/2, y0);
            cairo_curve_to (cr, x1, y0, x1, y0, x1, (y0 + y1)/2);
            cairo_curve_to (cr, x1, y1, x1, y1, (x1 + x0)/2, y1);
            cairo_curve_to (cr, x0, y1, x0, y1, x0, (y0 + y1)/2);
            cairo_close_path (cr);
            cairo_set_source_rgba (cr, 0.2, 0.8, 0.2,0.2);
            cairo_fill_preserve (cr);
            cairo_set_source_rgba (cr, 0.01, 0.01, 0.01, 0.8);
            cairo_set_line_width (cr, 3.0);
            cairo_stroke (cr);

            double farbe = 0.0, farbe1 = 1.0;
            if ((GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->live_viewin[0]*500.0 < 1.5) &&(GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->live_viewin[0]*500.0 > -1.5))
            {
                farbe = 1.0;
                farbe1 = 0.0;
            }
            float wave_go = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->live_view[0]*500.0;
            float wave_come = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->live_viewin[0]*500.0;
            float wave_db = log(fabs( GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->live_view[0]))*6/log(2);
            float wave_dbin = log(fabs( GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->live_viewin[0]))*6/log(2);
            double xl = floor(exp(log(1.055)*2.1*wave_db)*285);
            double xi = floor(exp(log(1.055)*2.1*wave_dbin)*285);
            if (xl > 225.0)   xl = 225.0;
            else if (xl < -225.0)   xl = -225.0;
            if (xi > 225.0)   xi = 225.0;
            else if (xi < -225.0)   xi = -225.0;
            double redline = 0.2;
            double redlinein = 0.2;
            if (wave_go > 75.0)
            {
                redline = 1.0;
                wave_go = 75.0;
            }
            else if (wave_go < -75.0)
            {
                redline = 1.0;
                wave_go = -75.0;
            }
            if (wave_come > 75.0)
            {
                redlinein = 1.0;
                wave_come = 75.0;
            }
            else if (wave_come < -75.0)
            {
                redlinein = 1.0;
                wave_come = -75.0;
            }
            cairo_set_source_rgba (cr,  redline, 1.0, 0.2,0.2);
            cairo_set_line_width (cr, 1.0);
            cairo_move_to (cr, liveviewx, liveviewy+25);
            cairo_curve_to (cr, liveviewx+75+wave_go,liveviewy+25-wave_go, liveviewx+150+wave_go,liveviewy+25+wave_go, liveviewx+225+wave_go,liveviewy+25);
            cairo_curve_to (cr, liveviewx+300+wave_go,liveviewy+25-wave_go, liveviewx+375+wave_go,liveviewy+25+wave_go, liveviewx+450,liveviewy+25);
            cairo_close_path (cr);
            cairo_fill_preserve (cr);
            cairo_set_source_rgba (cr,  redline, 1.0, 0.2,0.5);
            cairo_stroke (cr);

            cairo_set_source_rgba (cr, farbe1, farbe,redlinein,0.2);
            cairo_set_line_width (cr, 1.0);
            cairo_move_to (cr, liveviewx, liveviewy+25);
            cairo_curve_to (cr, liveviewx+75+wave_come,liveviewy+25-wave_come, liveviewx+150+wave_come,liveviewy+25+wave_come, liveviewx+225+wave_come,liveviewy+25);
            cairo_curve_to (cr, liveviewx+300+wave_come,liveviewy+25-wave_come, liveviewx+375+wave_come,liveviewy+25+wave_come, liveviewx+450,liveviewy+25);
            cairo_close_path (cr);
            cairo_fill_preserve (cr);
            cairo_set_source_rgba (cr, farbe1, farbe,redlinein,0.5);
            cairo_stroke (cr);

            double dashes[] = {5.0, 1.0 };
            cairo_set_dash (cr, dashes, 2, -0.25);

            cairo_move_to (cr, liveviewx+225, liveviewy+50);
            cairo_line_to (cr, liveviewx+225+xl, liveviewy+50);
            cairo_move_to (cr, liveviewx+225, liveviewy+50);
            cairo_line_to (cr, liveviewx+225-xl, liveviewy+50);
            cairo_set_source_rgba (cr,  redline, 1.0, 0.2,0.8);
            cairo_set_line_width (cr, 3.0);
            cairo_stroke (cr);

            cairo_set_dash (cr, dashes, 2, -0.25);
            cairo_move_to (cr, liveviewx+225, liveviewy);
            cairo_line_to (cr, liveviewx+225+xi, liveviewy);
            cairo_move_to (cr, liveviewx+225, liveviewy);
            cairo_line_to (cr, liveviewx+225-xi, liveviewy);

            cairo_set_source_rgba (cr,  redlinein, 1.0, 0.2,0.8);
            cairo_set_line_width (cr, 3.0);
            cairo_stroke (cr);
            cairo_destroy(cr);
        }

        else if (scaletype == 3)
        {
            // int bufsize = 450;
            int speedy = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->speed;
            int bufspeed = 450/speedy;
            double x0      = liveviewx+476,
                             y0      = liveviewy+39,
                                       rect_width  = 40.,
                                                     rect_height = 15.;
            double x1,y1;

            x1=x0+rect_width;
            y1=y0+rect_height;
            cairo_move_to  (cr, x0, (y0 + y1)/2);
            cairo_curve_to (cr, x0 ,y0, x0, y0, (x0 + x1)/2, y0);
            cairo_curve_to (cr, x1, y0, x1, y0, x1, (y0 + y1)/2);
            cairo_curve_to (cr, x1, y1, x1, y1, (x1 + x0)/2, y1);
            cairo_curve_to (cr, x0, y1, x0, y1, x0, (y0 + y1)/2);
            cairo_close_path (cr);
            cairo_set_source_rgba (cr, 0.2, 0.8, 0.2,0.2);
            cairo_fill_preserve (cr);
            cairo_set_source_rgba (cr, 0.01, 0.01, 0.01, 0.8);
            cairo_set_line_width (cr, 3.0);
            cairo_stroke (cr);

            float wave_go = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->live_view[0]*100.0;
        //    float wave_db = log(fabs( wave_go*0.002))*6/log(2);
         //   double xl = floor(exp(log(1.055)*2.1*wave_db)*285);
         //   if (xl > 225.0)   xl = 225.0;
         //   else if (xl < -225.0)   xl = -225.0;
            double redline = 0.2;
            if (wave_go > 25.0)
            {
                redline = 1.0;
                wave_go = 25.0;
            }
            else if (wave_go < -25.0)
            {
                redline = 1.0;
                wave_go = -25.0;
            }

            GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wave_save[GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->ringis] = wave_go;

          //  cairo_set_source_rgba (cr,  redline, 1.0, 0.2,0.8);
            cairo_set_line_width (cr, 1.0);
            cairo_move_to (cr, liveviewx+450, liveviewy+25);
           int ringisnow = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->ringis;
            for (int i=0; i<(bufspeed); i++)
            {
                if (ringisnow > bufspeed) ringisnow = 0;
                cairo_line_to (cr, liveviewx+450- speedy-(i*speedy), liveviewy+25+GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wave_save[ringisnow]);
                ringisnow +=1;
            } 


           GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->ringis -= 1;
           if (GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->ringis < 0) GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->ringis = bufspeed;
          /*  for (int i=1; i<(bufspeed); i++)
            {
                GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wave_save[(bufspeed)-i] = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wave_save[(bufspeed)-(i+1)];
            } */

	    cairo_pattern_t *linpat;
	    linpat = cairo_pattern_create_linear (450, 0, 450, 42);
	    cairo_pattern_set_extend(linpat, CAIRO_EXTEND_REFLECT);
	    cairo_pattern_add_color_stop_rgba (linpat, 0.2, 1, 0.2, 0,0.8);
	    cairo_pattern_add_color_stop_rgba (linpat, 0.8, redline, 1, 0.2,0.8);
	    cairo_set_source (cr, linpat);
       
            cairo_stroke (cr);
            cairo_pattern_destroy (linpat);
            cairo_destroy(cr);
        }
    }

    else if (    waveview->waveview_type == 2)
    {

        int liveviewx = widget->allocation.x, liveviewy = widget->allocation.y;
        liveviewx += (widget->allocation.width - GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->liveview_x) *0.5+15;
        liveviewy += (widget->allocation.height - GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->liveview_y) *0.5+15;

 
        if (GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->new_pig == 0)
        {
            cairo_t *     cr =       gdk_cairo_create(GDK_DRAWABLE(widget->window));
            cairo_pattern_t *pat;
            pat = cairo_pattern_create_radial (-130.4, -270.4, 1.6, -1.4,  -4.4, 300.0);
            cairo_pattern_add_color_stop_rgba (pat, 0, 0.2, 0.2, 0.3, 1);
            cairo_pattern_add_color_stop_rgba (pat, 1, 0.05, 0.05, 0.05, 1);
            cairo_set_source_rgb(cr, 0.05, 0.05, 0.05);
            cairo_rectangle (cr, liveviewx-5, liveviewy-5, 460, 60);
            cairo_set_source (cr, pat);
            cairo_fill (cr);
            cairo_pattern_destroy (pat);

            cairo_set_line_width (cr, 10);
            cairo_set_source_rgba (cr, 0, 0, 0,0.4);
            cairo_rectangle (cr, liveviewx-5, liveviewy-5, 460, 60);
            cairo_stroke (cr);
            cairo_set_line_width (cr, 1);
            cairo_set_source_rgba (cr, 0.1, 0.1, 0.1,0.7);
            cairo_rectangle (cr, liveviewx-6, liveviewy-6, 462, 62);
            cairo_stroke (cr);
            cairo_set_line_width (cr, 1);
            cairo_set_source_rgba (cr, 0.5, 0.5, 0.5,0.1);
            cairo_rectangle (cr, liveviewx-12, liveviewy-12, 474, 74);
            cairo_rectangle (cr, liveviewx-2, liveviewy-2, 454, 54);
            cairo_stroke (cr);

            cairo_set_line_width (cr, 1.5);
            cairo_set_source_rgba (cr,0.2, 1.0, 0.2, 0.4);
            cairo_move_to (cr, liveviewx, liveviewy+25);
            cairo_line_to (cr, liveviewx+450, liveviewy+25);
            cairo_stroke (cr);
            cairo_set_source_rgba (cr,0.2, 1.0, 0.2, 0.4);
            cairo_rectangle (cr, liveviewx, liveviewy, 450.0, 50.0);
            cairo_stroke (cr);
            int gitter = 0;
            for (int i=0; i<45; i++)
            {
                gitter += 10;
                cairo_move_to (cr, liveviewx+gitter-5, liveviewy);
                cairo_line_to (cr, liveviewx+gitter-5, liveviewy+50);
            }
            gitter = 0;
            for (int i=0; i<5; i++)
            {
                gitter += 10;
                cairo_move_to (cr, liveviewx, liveviewy+gitter-5);
                cairo_line_to (cr, liveviewx+450, liveviewy+gitter-5);
            }
            cairo_set_source_rgba (cr,0.2,  1.0, 0.2, 0.05);
            cairo_stroke (cr);
            cairo_destroy(cr);

            GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->new_pig += 1;

            gdk_pixbuf_get_from_drawable( GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->liveview_image,GDK_DRAWABLE(widget->window), gdk_colormap_get_system (),liveviewx-15, liveviewy-15,0,0,480,80);
        } 
         gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->liveview_image, 0,0,liveviewx-15, liveviewy-15 , 480, 80, GDK_RGB_DITHER_NORMAL, 0, 0);
       }

    return TRUE;
}

gboolean GtkWaveView::gtk_waveview_set_value (GtkWidget *cwidget, gpointer data )
{
    new_wave = 1;
    return TRUE;
}

static gboolean gtk_waveview_pointer_motion (GtkWidget *widget, GdkEventMotion *event)
{
    g_assert(GTK_IS_WAVEVIEW(widget));
    GtkWaveView *waveview = GTK_WAVEVIEW(widget);
    if (    waveview->waveview_type == 0)
    {
        if (GTK_WIDGET_HAS_GRAB(widget))
        {
            gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->waveview_image, 0,0, 0, 0, 300, 200, GDK_RGB_DITHER_NORMAL, 0, 0);
            GdkGC * line = gdk_gc_new(GDK_DRAWABLE(widget->window));
            GdkColor color ;
            gdk_gc_set_function(line, GDK_OR);
            color.red = 50 * 236;
            color.blue = 50 * 236;
            color.green = 70 * 236;
            gdk_gc_set_rgb_fg_color(line, &color);
            gdk_gc_set_line_attributes (line, 1,GDK_LINE_SOLID,GDK_CAP_BUTT,GDK_JOIN_MITER);
            if (GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wavebutton  == 1)
            {
                gdk_draw_rectangle(GDK_DRAWABLE(widget->window), line,TRUE, waveview->start_x, 0,event->x-waveview->start_x,200);
                GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->waveleft = event->x-waveview->start_x;
                GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wavestay = waveview->start_x;
            }
            else if (GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wavebutton  == 2)
            {
                gdk_draw_rectangle(GDK_DRAWABLE(widget->window), line,TRUE, event->x, 0,GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->waveleft,200);
                GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wavestay = event->x;
            }
            else if (GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wavebutton  == 3)
            {
                gdk_draw_rectangle(GDK_DRAWABLE(widget->window), line,TRUE, GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wavestay, 0,event->x-GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wavestay,200);
                GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->waveleft = event->x-GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wavestay;
            }
            g_object_unref(line );
            GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->offset_cut = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wavestay/GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->drawscale;
            GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->length_cut = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->waveleft/GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->drawscale;
            offcut = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->offset_cut ;
            if (GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->offset_cut < 0)
            {
                offcut = 0 ;
                GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->length_cut += GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->offset_cut;
                GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->offset_cut = 0;
            }
            lenghtcut = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->length_cut ;
            if (GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->length_cut + GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->offset_cut > GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->filelength)
            {
                lenghtcut = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->filelength-GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->offset_cut;
                GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->length_cut = lenghtcut;
            }
            string partion, tip;
            tip = "offset (";
            IntToString((offcut), partion);
            tip += partion;
            tip += ")  length (";
            IntToString((lenghtcut), partion);
            tip += partion;
            tip += ") ";
            gtk_widget_set_sensitive(widget, TRUE);
            gtk_tooltips_set_tip (GTK_TOOLTIPS (GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->comandline), widget, tip.c_str(), "the offset and length.");
        }
        gdk_pixbuf_get_from_drawable( GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigwaveview_image,GDK_DRAWABLE(widget->window), gdk_colormap_get_system (),0,0,0,0,300,200);
    }
    else     if (    waveview->waveview_type ==  1)
    {

    }
    return FALSE;
}

static gboolean gtk_waveview_button_press (GtkWidget *widget, GdkEventButton *event)
{
    g_assert(GTK_IS_WAVEVIEW(widget));
    GtkWaveView *waveview = GTK_WAVEVIEW(widget);
    gtk_widget_grab_focus(widget);
    gtk_widget_grab_default (widget);
    gtk_grab_add(widget);
    if (    waveview->waveview_type == 0)
    {
        if (event->button == 1)
        {
            waveview->start_x = event->x;
            waveview->start_y = event->y;
            GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wavebutton = 1;
        }
        else if (event->button == 2)
        {
            GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wavebutton = 2;
        }
        else if (event->button == 3)
        {
            gdk_draw_pixbuf(GDK_DRAWABLE(widget->window), widget->style->fg_gc[0], GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->waveview_image, 0,0, 0, 0, 300, 200, GDK_RGB_DITHER_NORMAL, 0, 0);
            gdk_pixbuf_get_from_drawable( GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->bigwaveview_image,GDK_DRAWABLE(widget->window), gdk_colormap_get_system (),0,0,0,0,300,200);
            GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->offset_cut = 0;
            GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->length_cut = 0;
            GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wavebutton = 3;
            offcut = 0;
            lenghtcut = 0;
            string partion, tip;
            tip = "offset is  ";
            IntToString((offcut), partion);
            tip += partion;
            tip += "  length is  ";
            IntToString((lenghtcut), partion);
            tip += partion;
            gtk_widget_set_sensitive(widget, TRUE);
            gtk_tooltips_set_tip (GTK_TOOLTIPS (GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->comandline), widget, tip.c_str(), "the offset and length.");
        }
    }
    else     if (    waveview->waveview_type == 1)
    {

        int liveviewx = widget->allocation.x, liveviewy = widget->allocation.y;
        liveviewx += (widget->allocation.width - GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->liveview_x) *0.5+475;
        liveviewy += (widget->allocation.height - GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->liveview_y) *0.5+15;
        if ((event->button == 1)&&(event->x < liveviewx +55) &&(event->x > liveviewx+10) &&(event->y < liveviewy+54) &&(event->y > liveviewy-5) )
        {
            double        y0      = liveviewy-5 ;
            if ((event->x < liveviewx +55) &&(event->x > liveviewx+10) &&(event->y < liveviewy+10) &&(event->y > liveviewy-5) )
            {
                y0      = liveviewy-5;
                GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->mode = 1;
            }
            else if ((event->x < liveviewx +55) &&(event->x > liveviewx+10) &&(event->y < liveviewy+39) &&(event->y > liveviewy+17) )
            {
                y0      = liveviewy+17;
                GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->mode = 2;
            }
            else if ((event->x < liveviewx +55) &&(event->x > liveviewx+10) &&(event->y < liveviewy+54) &&(event->y > liveviewy+39) )
            {
                y0      = liveviewy+39;
                GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->mode = 3;
                for (int i=0; i<449; i++) GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wave_save[i+1] = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wave_save[i] = 0;
            }

            cairo_t *     cr =       gdk_cairo_create(GDK_DRAWABLE(widget->window));
            double x0      = liveviewx+16,
                             rect_width  = 40.,
                                           rect_height = 15.;
            double x1,y1;

            x1=x0+rect_width;
            y1=y0+rect_height;
            cairo_move_to  (cr, x0, (y0 + y1)/2);
            cairo_curve_to (cr, x0 ,y0, x0, y0, (x0 + x1)/2, y0);
            cairo_curve_to (cr, x1, y0, x1, y0, x1, (y0 + y1)/2);
            cairo_curve_to (cr, x1, y1, x1, y1, (x1 + x0)/2, y1);
            cairo_curve_to (cr, x0, y1, x0, y1, x0, (y0 + y1)/2);
            cairo_close_path (cr);
            cairo_set_source_rgba (cr, 0.8, 0.8, 0.9,0.6);
            cairo_fill_preserve (cr);
            cairo_set_source_rgba (cr, 0.01, 0.01, 0.01, 0.3);
            cairo_set_line_width (cr, 3.0);
            cairo_stroke (cr);

            x1=x0+rect_width-2;
            y1=y0+rect_height-2;
            cairo_move_to  (cr, x0+2, (y0+2 + y1)/2);
            cairo_curve_to (cr, x0+2 ,y0+2, x0+2, y0+2, (x0+2 + x1)/2, y0+2);
            cairo_curve_to (cr, x1, y0+2, x1, y0+2, x1, (y0+2 + y1)/2);
            cairo_curve_to (cr, x1, y1, x1, y1, (x1 + x0+2)/2, y1);
            cairo_curve_to (cr, x0+2, y1, x0+2, y1, x0+2, (y0+2 + y1)/2);
            cairo_close_path (cr);
            cairo_move_to  (cr, x0, (y0 + y1)/2);
            cairo_curve_to (cr, x0 ,y0, x0, y0, (x0 + x1)/2, y0);
            cairo_curve_to (cr, x1, y0, x1, y0, x1, (y0 + y1)/2);
            cairo_curve_to (cr, x1, y1, x1, y1, (x1 + x0)/2, y1);
            cairo_curve_to (cr, x0, y1, x0, y1, x0, (y0 + y1)/2);
            cairo_close_path (cr);
            cairo_set_source_rgba (cr, 0.5, 1, 0.5, 0.9);
            cairo_set_line_width (cr, 1.5);
            cairo_stroke (cr);
            cairo_destroy(cr);
        }
    }
    return TRUE;
}

static gboolean gtk_waveview_button_release (GtkWidget *widget, GdkEventButton *event)
{
    g_assert(GTK_IS_WAVEVIEW(widget));
    if (GTK_WIDGET_HAS_GRAB(widget))
        gtk_grab_remove(widget);
    return FALSE;
}

//----------- set value from mouseweel
static gboolean gtk_waveview_scroll (GtkWidget *widget, GdkEventScroll *event)
{
    g_assert(GTK_IS_WAVEVIEW(widget));
    GtkWaveView *waveview = GTK_WAVEVIEW(widget);
    if ((waveview->waveview_type == 1) && (GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->mode == 3))
    {
        int setspeed;
        if (event->direction == 0) setspeed = -1;
        else setspeed = 1;
        GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->speed += setspeed;
        //gtk_regler_set_value(widget, event->direction);
        if ((GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->speed <75) && (GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->speed >12)) GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->speed = 10;
        if (GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->speed >10)  GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->speed = 75;

        if (GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->speed <1) GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->speed = 1;
    //    for (int i=450/GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->speed; i<450; i++) GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wave_save[i+1] = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wave_save[i] = 0;
    for (int i=0; i<450; i++)  GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wave_save[i] = 0;
GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->ringis = 450/GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->speed;
// fprintf (stderr, "%i weel %i \n" , GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->speed, setspeed);
    }
    return FALSE;
}

//----------- set size for GdkDrawable per type
static void gtk_waveview_size_request (GtkWidget *widget, GtkRequisition *requisition)
{
    g_assert(GTK_IS_WAVEVIEW(widget));
    GtkWaveView *waveview = GTK_WAVEVIEW(widget);
    if (    waveview->waveview_type == 0)
    {
        requisition->width = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->waveview_x;
        requisition->height = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->waveview_y;
    }
    else     if (    waveview->waveview_type == 1)
    {
        requisition->width = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->liveview_x;
        requisition->height = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->liveview_y;
    }
    else     if (    waveview->waveview_type == 2)
    {
        requisition->width = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->liveview_x;
        requisition->height = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->liveview_y;
    }
}

//----------- init the GtkWaveViewClass
static void gtk_waveview_class_init (GtkWaveViewClass *klass)
{
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS(klass);
    klass->waveview_x = 300;
    klass->waveview_y = 200;
    klass->liveview_x = 530;
    klass->liveview_y = 80;
    klass->livecontrol_x = 50;
    klass->livecontrol_y = 80;
    klass->mode = 1;
    klass->speed = 5;
    klass->wave_save= new float[451];
    for (int i=0; i<450; i++) klass->wave_save[i+1] = klass->wave_save[i] = 0;
    klass->ringis = 450/5;

    widget_class->expose_event = gtk_waveview_expose;
    widget_class->size_request = gtk_waveview_size_request;
    widget_class->button_press_event = gtk_waveview_button_press;
    widget_class->button_release_event = gtk_waveview_button_release;
    widget_class->motion_notify_event = gtk_waveview_pointer_motion;
    widget_class->scroll_event = gtk_waveview_scroll;

    klass->waveview_image = gdk_pixbuf_new(GDK_COLORSPACE_RGB,FALSE,8,300,200);
    g_assert(klass->waveview_image != NULL);
    klass->bigwaveview_image = gdk_pixbuf_new(GDK_COLORSPACE_RGB,FALSE,8,300,200);
    g_assert(klass->bigwaveview_image != NULL);
    klass->liveview_image = gdk_pixbuf_new(GDK_COLORSPACE_RGB,FALSE,8,480,80);
    g_assert(klass->liveview_image != NULL);
    klass->livecontrol_image = gdk_pixbuf_new(GDK_COLORSPACE_RGB,FALSE,8,50,80);
    g_assert(klass->liveview_image != NULL);
}

//----------- init the WaveView type
static void gtk_waveview_init (GtkWaveView *waveview)
{
    GtkWidget *widget = GTK_WIDGET(waveview);
    GTK_WIDGET_SET_FLAGS (GTK_WIDGET(waveview), GTK_CAN_FOCUS);
    GTK_WIDGET_SET_FLAGS (GTK_WIDGET(waveview), GTK_CAN_DEFAULT);
    if (waveview->waveview_type == 0)
    {
        widget->requisition.width = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->waveview_x;
        widget->requisition.height = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->waveview_y;
    }
    else if (waveview->waveview_type == 1)
    {
        widget->requisition.width = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->liveview_x;
        widget->requisition.height = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->liveview_y;
    }
    else if (waveview->waveview_type == 2)
    {
        widget->requisition.width = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->liveview_x;
        widget->requisition.height = GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->liveview_y;
    }
}

//----------- redraw when value changed
static gboolean gtk_waveview_value_changed(gpointer obj)
{
    GtkWidget *widget = (GtkWidget *)obj;
    gtk_widget_queue_draw(widget);
    return FALSE;
}

void GtkWaveView::gtk_waveview_destroy (GtkWidget *weidget, gpointer data )
{
    GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_WAVEVIEW, NULL ));
    g_assert(GTK_IS_WAVEVIEW(widget));
    if (G_IS_OBJECT(GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))-> waveview_image)) 
    g_object_unref(GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))-> waveview_image);
    if (G_IS_OBJECT(GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))-> bigwaveview_image)) 
    g_object_unref(GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))-> bigwaveview_image);
    if (G_IS_OBJECT(GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))-> liveview_image)) 
    g_object_unref(GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->liveview_image);
    if (G_IS_OBJECT(GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))-> livecontrol_image)) 
    g_object_unref(GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->livecontrol_image);
    if(GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wave_save) 
    delete[] GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->wave_save;
}

//----------- create waveview widget
GtkWidget *GtkWaveView::gtk_wave_view(const char* file)
{
    GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_WAVEVIEW, NULL ));
    GtkWaveView *waveview = GTK_WAVEVIEW(widget);
    GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->fileview = file;
    new_wave = 1;
    waveview->waveview_type = 0;
    string partion, tip;
    tip = "offset (";
    IntToString((offcut), partion);
    tip += partion;
    tip += ")  length (";
    IntToString((lenghtcut), partion);
    tip += partion;
    tip += ") ";
    gtk_widget_set_sensitive(widget, TRUE);
    GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->comandline = gtk_tooltips_new ();
    gtk_tooltips_set_tip (GTK_TOOLTIPS (GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->comandline), widget, tip.c_str(), "the offset and length.");
    return widget;
}

//----------- create live waveview widget
GtkWidget *GtkWaveView::gtk_wave_live_view(float* outfloat, float* infloat,GtkAdjustment *_adjustment)
{
    GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_WAVEVIEW, NULL ));
    GtkWaveView *waveview = GTK_WAVEVIEW(widget);
    GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->live_view = outfloat;
    GTK_WAVEVIEW_CLASS(GTK_OBJECT_GET_CLASS(widget))->live_viewin = infloat;

    waveview->waveview_type = 1;
    if (widget)
    {
        gtk_range_set_adjustment(GTK_RANGE(widget), _adjustment);
        gtk_signal_connect(GTK_OBJECT(widget), "value-changed", G_CALLBACK(gtk_waveview_value_changed), widget);
    }
    return widget;
}

//----------- create live waveview widget
GtkWidget *GtkWaveView::gtk_wave_place_hold()
{
    GtkWidget *widget = GTK_WIDGET( g_object_new (GTK_TYPE_WAVEVIEW, NULL ));
    GtkWaveView *waveview = GTK_WAVEVIEW(widget);
    waveview->waveview_type = 2;
    return widget;
}

//----------- get the WaveView type
GType gtk_waveview_get_type (void)
{
    static GType kn_type = 0;
    if (!kn_type)
    {
        static const GTypeInfo kn_info =
        {
            sizeof(GtkWaveViewClass), NULL,  NULL, (GClassInitFunc)gtk_waveview_class_init, NULL, NULL, sizeof (GtkWaveView), 0, (GInstanceInitFunc)gtk_waveview_init
        };
        kn_type = g_type_register_static(GTK_TYPE_RANGE,  "GtkWaveView", &kn_info, (GTypeFlags)0);
    }
    return kn_type;
}

