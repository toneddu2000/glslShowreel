ppcolor
{
	program ton_pp_basic
	{
		map $rt:ppcolor
	}
	{
		map $sourcedepth
	}
	
}

ppdepth
{
	program ton_pp_depth
	{
		map $rt:ppdepth
	}
	{
		map $sourcedepth
	}
}

ppbandw
{
	program ton_pp_bandw
	{
		map $rt:ppbandw
	}
}

ppmblur
{
	program ton_pp_motionblur
	{
		map $rt:ppmblur
	}
}

ppchrom
{
	program ton_pp_chromaticaberration
	{
		map $rt:ppchrom
	}
}

ppascii
{
	program ton_pp_ascii
	{
		map $rt:ppascii
	}
}

ppbloom
{
	program ton_pp_bloom
	{
		map $rt:ppbloom
	}
}

ppmedian
{
	program ton_pp_median
	{
		map $rt:ppmedian
	}
}

postproc_basic
{
	program postproc_basic
	affine
	{
		map $sourcecolour
		nodepthtest
	}
}

postproc_median
{
	program postproc_median
	affine
	{
		map $sourcecolour
		nodepthtest
	}
}

postproc_ascii
{
	program postproc_ascii
	affine
	{
		map $sourcecolour
		nodepthtest
	}
}

postproc_chr_aberration
{
	program postproc_chr_aberration
	{
		map $sourcecolour
	}
	{
		map $sourcedepth
	}
}

postproc_mblur
{
	program postproc_mblur
	{
		map $sourcecolour
	}
	{
		map $sourcedepth
	}
}

postproc_bw
{
	program postproc_bw
	affine
	{
		map $sourcecolour
		nodepthtest
	}
}

postproc_bloom
{
	program postproc_bloom
	affine
	{
		map $sourcecolour
		nodepthtest
	}
}

postproc_pixelate
{
	program postproc_ascii
	affine
	{
		map $sourcecolour
		nodepthtest
	}
}